#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#include <omp.h>
#define MAXGPU 2
#define MAXN 2048
#define MAXM 2
#define GPULOCAL 16
char hostMtx[2][MAXN*MAXN];

int N, M, binN;
char clSrcFormat[32767] = ""; 
char clSrc[32767] = "";
// -- start working with OpenCL
const int clNeedDevCnt = 1;
cl_context				clCtx[2];
cl_program				clPrg[2];
cl_kernel				clKrn[2];
cl_command_queue		clQue[2];
cl_mem					clMemIn[2][MAXM];

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
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
		if (clKrn[i])	clReleaseKernel(clKrn[i]);
		if (clPrg[i])		clReleaseProgram(clPrg[i]);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clQue[i])	
			clReleaseCommandQueue(clQue[i]);
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clCtx[i])	clReleaseContext(clCtx[i]);
	}
	exit(0);
}
int initAllGPU(char fileName[], clFuncArgs) {
	// -- generate kernel code
	FILE *codefin = fopen(fileName, "r");
	assert(codefin != NULL);
	assert(fread(clSrcFormat, 1, 32767, codefin) < 32767);
	sprintf(clSrc, clSrcFormat, N, binN);
	size_t clSrcLen = strlen(clSrc);
	fclose(codefin);

	cl_int					clStat;
	cl_uint					clPlatN, clGPUN, clDevN;
	cl_platform_id			clPlatID;
	cl_device_id			clGPUID[MAXGPU];
	const char				*clSrcPtr = clSrc;

	// -- basic OpenCL setup
	clGetPlatformIDs(1, &clPlatID, &clPlatN);
	clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, MAXGPU, clGPUID, &clDevN);
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
		clStat = clBuildProgram(clPrg[i], 1, clGPUID+i, NULL, NULL, NULL);
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
	size_t globalOffset[] = {0, 0};
	size_t globalSize[] = {binN, binN};
	size_t localSize[] = {GPULOCAL, GPULOCAL};
	int flag = 0;
	for (int it = 0; it < M; it++) {
		// -- set argument to kernel
		clStat = clSetKernelArg(clKrn[0], 0, sizeof(cl_mem), &clMemIn[0][flag]);
		CheckFailAndExit(clStat);
		clStat = clSetKernelArg(clKrn[0], 1, sizeof(cl_mem), &clMemIn[0][!flag]);
		CheckFailAndExit(clStat);

		// -- execute
		clStat = clEnqueueNDRangeKernel(clQue[0], clKrn[0], 2, globalOffset,
				globalSize, localSize, 0, NULL, NULL);
		CheckFailAndExit(clStat);
		flag = !flag;
	}
	// -- read back
	clStat = clEnqueueReadBuffer(clQue[0], clMemIn[0][flag], CL_TRUE, 0,
			sizeof(char)*binN*binN, hostMtx[flag], 0, NULL, NULL);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			putchar(hostMtx[flag][i*binN+j]+'0');
		puts("");
	}

	return 1;
}
int executeCPU() {
	// game of life
	int flag = 0;
	int chunk = 64;
	for (int it = 0; it < M; it++) {
#pragma omp parallel for schedule(static, chunk)
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int adj = 
					(i-1 >= 0 && j-1 >= 0 && hostMtx[flag][(i-1)*binN + j-1]) + 
					(i-1 >= 0 && hostMtx[flag][(i-1)*binN+j]) + 
					(i-1 >= 0 && j+1 < binN && hostMtx[flag][(i-1)*binN+j+1]) +
					(j-1 >= 0 && hostMtx[flag][i*binN+j-1]) + 
					(j+1 < binN && hostMtx[flag][i*binN+j+1]) +
					(i+1 < binN && j-1 >= 0 && hostMtx[flag][(i+1)*binN+j-1]) + 
					(i+1 < binN && hostMtx[flag][(i+1)*binN+j]) + 
					(i+1 < binN && j+1 < binN && hostMtx[flag][(i+1)*binN+j+1]);
				hostMtx[!flag][i*binN+j] = (hostMtx[flag][i*binN+j] == 0 && adj == 3) ||
					(hostMtx[flag][i*binN+j] == 1 && (adj == 2 || adj == 3));
			}
		}
		flag = !flag;
	}	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			putchar(hostMtx[flag][i*binN+j]+'0');
		puts("");
	}
}
void onStart(clFuncArgs) {
	assert(scanf("%d %d", &N, &M) == 2);
	static char str[2048][2048];
	for (int i = 0; i < N; i++)
		assert(scanf("%s", str[i]) == 1);
	binN = N;
	while (binN % GPULOCAL)
		binN++;
	for (int i = 0; i < binN; i++) {
		for (int j = 0; j < binN; j++) {
			if (i < N && j < N) {
				hostMtx[0][i*binN + j] = str[i][j] - '0';
			} else {
				hostMtx[0][i*binN + j] = 0;
			}
		}
	}	
//	executeCPU();
	initAllGPU("game-of-life.cl", clCallFunc);
	executeGPU(clCallFunc);
	return ;
	/*
	   int procN = 0;
	   Node *procBuff[32];
	   while (readIn()) {
	   int expr_len = strlen(expr);
	   Node *root = parseExpr(0, expr_len-1, expr, procN, clCallFunc);
	   procBuff[procN++] = root;
	   if (procN == clNeedDevCnt) {
	// executeCPU(root);
	executeGPU(procBuff, procN, clCallFunc);
	procN = 0;
	}
	}
	executeGPU(procBuff, procN, clCallFunc);
	destroyGPU(clCallFunc);
	 */
}

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
