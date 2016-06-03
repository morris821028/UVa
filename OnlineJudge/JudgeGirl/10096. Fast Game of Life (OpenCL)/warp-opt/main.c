#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#include <omp.h>
#define OPENCL_MAXGPU 2
#define KERNEL_CODE_LEN 32767

#define MAXN 2048
#define MAXM 2
char hostMtx[2][MAXN*MAXN];

int N, M, binN;
// -- start working with OpenCL
const int clNeedDevCnt = 1;

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrn, clQue, clMemIn); \
	}
#define clFuncArgs cl_context clCtx[], cl_program clPrg[], cl_kernel clKrn[], \
	cl_command_queue clQue[], cl_mem clMemIn[][MAXM]
#define clCallFunc clCtx, clPrg, clKrn, clQue, clMemIn
#define clCallFuncOuter clCtx, clPrg, clKrn, clQue, clMemIn

void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	for (int i = 0; i < clNeedDevCnt; i++) {
		for (int j = 0; j < M; j++) { 
			if (clMemIn[i][j])
				clReleaseMemObject(clMemIn[i][j]);
		}
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clKrn[i])
			clReleaseKernel(clKrn[i]);
		if (clPrg[i])
			clReleaseProgram(clPrg[i]);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clQue[i])	
			clReleaseCommandQueue(clQue[i]);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clCtx[i])
			clReleaseContext(clCtx[i]);
	}
	exit(0);
}
int initAllGPU(char fileName[], clFuncArgs) {
static char clSrcFormat[KERNEL_CODE_LEN] = 
"#define N %d\n"
"#define M %d\n"
"#define CTYPE char\n"
"__kernel void simulate(__global CTYPE *IN,\n"
"        __global CTYPE *OUT) {\n"
"    int id = get_global_id(0);\n"
"        int x = id / M+1, y = id % M +1;\n"
"#define G(x, y) IN[(x) * N + (y)]\n"
"        char t = G(x, y);\n"
"        char adj = G(x-1, y-1) + G(x-1, y) + G(x-1, y+1) + G(x, y-1) + G(x, y+1)\n"
"                        + G(x+1, y-1) + G(x+1, y) + G(x+1, y+1);\n"
"        OUT[x * N + y] = (t == 0 && adj == 3) || (t == 1 && (adj == 2 || adj == 3));\n"
"}"; 
	static char clSrc[KERNEL_CODE_LEN] = "";

	// -- generate kernel code
//	FILE *codefin = fopen(fileName, "r");
//	assert(codefin != NULL);
//	assert(fread(clSrcFormat, 1, KERNEL_CODE_LEN, codefin) < KERNEL_CODE_LEN);
	sprintf(clSrc, clSrcFormat, N+2, N);
	size_t clSrcLen = strlen(clSrc);
//	fclose(codefin);

	cl_int					clStat;
	cl_uint					clPlatN, clGPUN, clDevN;
	cl_platform_id			clPlatID;
	cl_device_id			clGPUID[OPENCL_MAXGPU];
	const char				*clSrcPtr = clSrc;

	// -- basic OpenCL setup
	clGetPlatformIDs(1, &clPlatID, &clPlatN);
	clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, OPENCL_MAXGPU, clGPUID, &clDevN);
	assert(clDevN >= clNeedDevCnt);
	for (int i = 0; i < clNeedDevCnt; i++) {
		clCtx[i] = clCreateContext(NULL, 1, clGPUID+i, NULL, NULL, &clStat);
		CheckFailAndExit(clStat);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		clQue[i] = clCreateCommandQueue(clCtx[i], clGPUID[i], 
				0, &clStat);
		CheckFailAndExit(clStat);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		clPrg[i] = clCreateProgramWithSource(clCtx[i], 1, &clSrcPtr, &clSrcLen, &clStat);
		CheckFailAndExit(clStat);
		clStat = clBuildProgram(clPrg[i], 1, clGPUID+i, "-cl-fast-relaxed-math", NULL, NULL);
		if (clStat != CL_SUCCESS) {
			fprintf(stderr, "Error: Line %u in file %s\n\n", __LINE__, __FILE__);
			size_t log_size;
			clGetProgramBuildInfo(*clPrg, clGPUID[0],
					CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
			char *program_log = (char *) calloc(log_size+1, sizeof(char));
			clGetProgramBuildInfo(*clPrg, clGPUID[0],
					CL_PROGRAM_BUILD_LOG, log_size+1, program_log, NULL);
			printf("%s", program_log);
			free(program_log);
			CheckFailAndExit(CL_BUILD_PROGRAM_FAILURE);
		}
		clKrn[i] = clCreateKernel(clPrg[i], "simulate", &clStat);
		CheckFailAndExit(clStat);
	}

	// -- create all buffers
	cl_mem_flags clInBuffFlag = CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR;
	for (int d = 0; d < clNeedDevCnt; d++) {
		for (int i = 0; i < 2; i++) {
			clMemIn[d][i] = clCreateBuffer(clCtx[d], clInBuffFlag, 
				sizeof(char)*binN*binN, hostMtx[i], &clStat);
			CheckFailAndExit(clStat);
		}
	}

	return 1;
}
int executeGPU(clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {N*N};
	int flag = 0;
	for (int it = 0; it < M; it++) {
		// -- set argument to kernel
		clStat = clSetKernelArg(clKrn[0], 0, sizeof(cl_mem), &clMemIn[0][flag]);
		CheckFailAndExit(clStat);
		clStat = clSetKernelArg(clKrn[0], 1, sizeof(cl_mem), &clMemIn[0][!flag]);
		CheckFailAndExit(clStat);

		// -- execute
		clStat = clEnqueueNDRangeKernel(clQue[0], clKrn[0], 1, globalOffset,
				globalSize, 0, 0, NULL, NULL);
		CheckFailAndExit(clStat);
		flag = !flag;
	}
	// -- read back
	clStat = clEnqueueReadBuffer(clQue[0], clMemIn[0][flag], CL_TRUE, 0,
			sizeof(char)*binN*binN, hostMtx[flag], 0, NULL, NULL);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			hostMtx[flag][i*binN+j] += '0';
		puts(hostMtx[flag]+i*binN+1);
	}

	return 1;
}
void onStart(clFuncArgs) {
	assert(scanf("%d %d", &N, &M) == 2);
	while (getchar() != '\n');
	static char str[2048][2048];
	for (int i = 1; i <= N; i++)
		assert(fgets(str[i]+1, 2048, stdin) != NULL);
	binN = N+2;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			hostMtx[0][i*binN + j] = str[i][j] - '0';
	}	

	initAllGPU("game-of-life.cl", clCallFunc);
	executeGPU(clCallFunc);
	return ;
}

cl_context				clCtx[OPENCL_MAXGPU];
cl_program				clPrg[OPENCL_MAXGPU];
cl_kernel				clKrn[OPENCL_MAXGPU];
cl_command_queue		clQue[OPENCL_MAXGPU];
cl_mem					clMemIn[OPENCL_MAXGPU][MAXM];

void sigHandler(int signo) {
	printf("God Bless Me\n");
	destroyGPU(clCallFuncOuter);
	exit(0);
}
int main(int argc, char *argv[]) {
	const char sigErr[] = "I can't catch signal.\n";
	if (signal(SIGTRAP, sigHandler) == SIG_ERR)
		fprintf(stderr, sigErr);
	if (signal(SIGSEGV, sigHandler) == SIG_ERR)
		fprintf(stderr, sigErr);
	if (signal(SIGILL, sigHandler) == SIG_ERR)
		fprintf(stderr, sigErr);
	if (signal(SIGFPE, sigHandler) == SIG_ERR)
		fprintf(stderr, sigErr);
	if (signal(SIGKILL, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);
	if (signal(SIGINT, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);

	onStart(clCallFuncOuter);
	return 0;
}



