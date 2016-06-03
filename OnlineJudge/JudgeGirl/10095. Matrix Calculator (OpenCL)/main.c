#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#include <omp.h>
#define MAXGPU 1
#define MAXN 1024
#define MAXM 6
#define GPULOCAL 32
#define MAXMID 8
uint32_t	hostMtx[MAXM][MAXN*MAXN];
uint32_t	hostX[MAXN*MAXN], hostY[MAXN*MAXN];
int N, M, Q;
char clSrcFormat[32767] = ""; 
char clSrc[32767] = "";
// -- start working with OpenCL
const int clNeedDevCnt = 1;
cl_context				clCtx[2];
cl_program				clPrg[2];
cl_kernel				clKrnAdd[2], clKrnMul[2];
cl_command_queue		clQue[2];
cl_mem					clMemIn[2][MAXM], clMemMid[2][MAXMID];

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn); \
	}
#define clFuncArgs cl_context clCtx[], cl_program clPrg[], cl_kernel clKrnAdd[], \
	cl_kernel clKrnMul[], cl_command_queue clQue[], cl_mem clMemIn[][MAXM]
#define clCallFunc clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn
#define clCallFuncOuter clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn

uint32_t writeMatrixOut(int N, uint32_t *A) {
	uint32_t h = 0;
	uint32_t *Aend = A + N*N;
	for (; A != Aend; A++)
		h = (h + *A) * 2654435761LU;
	return h;
}
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	for (int i = 0; i < clNeedDevCnt; i++) {
		for (int j = 0; j < M; j++) { 
			if (clMemIn[i][j])
				clReleaseMemObject(clMemIn[i][j]);
		}
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		for (int j = 0; j < MAXMID; j++) {
			if (clMemMid[i][j])
				clReleaseMemObject(clMemMid[i][j]);
		}
	}
	for (int i = 0; i < clNeedDevCnt; i++) {
		if (clKrnAdd[i])	clReleaseKernel(clKrnAdd[i]);
		if (clKrnMul[i])	clReleaseKernel(clKrnMul[i]);
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
	sprintf(clSrc, clSrcFormat, N);
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
	clCtx[0] = clCreateContext(NULL, 1, clGPUID, NULL, NULL, &clStat);
	CheckFailAndExit(clStat);
	for (int i = 0; i < clNeedDevCnt; i++) {
		clQue[i] = clCreateCommandQueue(clCtx[0], clGPUID[i], 
				/*CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE*/ 0, &clStat);
		CheckFailAndExit(clStat);
	}
	clPrg[0] = clCreateProgramWithSource(clCtx[0], 1, &clSrcPtr, &clSrcLen, &clStat);
	CheckFailAndExit(clStat);
	clStat = clBuildProgram(clPrg[0], 1, clGPUID, NULL, NULL, NULL);
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
	clKrnAdd[0] = clCreateKernel(clPrg[0], "matrixAdd", &clStat);
	CheckFailAndExit(clStat);
	clKrnMul[0] = clCreateKernel(clPrg[0], "matrixMul", &clStat);
	CheckFailAndExit(clStat);

	// -- create all buffers
	cl_mem_flags clInBuffFlag = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
	for (int j = 0; j < clNeedDevCnt; j++) {
		for (int i = 0; i < M; i++) {
			clMemIn[j][i] = clCreateBuffer(clCtx[0], clInBuffFlag, sizeof(uint32_t)*N*N,
					hostMtx[i], &clStat);
			CheckFailAndExit(clStat);
		}
	}
	for (int j = 0; j < clNeedDevCnt; j++) {
		for (int i = 0; i < MAXMID; i++) {
			clMemMid[j][i] = clCreateBuffer(clCtx[0], CL_MEM_READ_WRITE, 
					sizeof(uint32_t)*N*N, NULL, &clStat);
			CheckFailAndExit(clStat);
		}
	}

	return 1;
}
void GPUmultiply(int N, int waitN, cl_event events[], cl_event *ret_event, 
		int devIdx, cl_mem *LIN, cl_mem *RIN, cl_mem *OUT, clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {N*N};
	size_t localSize[] = {GPULOCAL};
	// -- set argument to kernel
	clStat = clSetKernelArg(clKrnMul[0], 0, sizeof(cl_mem), LIN);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnMul[0], 1, sizeof(cl_mem), RIN);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnMul[0], 2, sizeof(cl_mem), OUT);
	CheckFailAndExit(clStat);

	// -- execute
	clStat = clEnqueueNDRangeKernel(clQue[devIdx], clKrnMul[0], 1, globalOffset,
			globalSize, NULL, waitN, events, ret_event);
	CheckFailAndExit(clStat);
}
void GPUadd(int N, int waitN, cl_event events[], cl_event *ret_event, 
		int devIdx, cl_mem *LIN, cl_mem *RIN, cl_mem *OUT, clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {N*N};
	// -- set argument to kernel
	clStat = clSetKernelArg(clKrnAdd[0], 0, sizeof(cl_mem), LIN);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnAdd[0], 1, sizeof(cl_mem), RIN);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnAdd[0], 2, sizeof(cl_mem), OUT);
	CheckFailAndExit(clStat);

	// -- execute
	clStat = clEnqueueNDRangeKernel(clQue[devIdx], clKrnAdd[0], 1, globalOffset,
			globalSize, NULL, waitN, events, ret_event);
	CheckFailAndExit(clStat);
}
int executeGPU(clFuncArgs) {
	cl_int clStat;
	cl_event events[4];
	// AB
	GPUmultiply(N, 0, NULL, &events[0], 0, &clMemIn[0]['A'-'A'], &clMemIn[0]['B'-'A'],
			&clMemMid[0][0], clCallFunc);
	fprintf(stderr, "AB\n");
	// CD
	GPUmultiply(N, 0, NULL, &events[1], 0, &clMemIn[0]['C'-'A'], &clMemIn[0]['D'-'A'],
			&clMemMid[0][1], clCallFunc);
	fprintf(stderr, "CD\n");

	// ABE
	GPUmultiply(N, 1, &events[0], &events[2], 0, &clMemMid[0][0], &clMemIn[0]['E'-'A'], 
			&clMemMid[0][2], clCallFunc);
	fprintf(stderr, "ABE\n");
	// CDF
	GPUmultiply(N, 1, &events[1], &events[3], 0, &clMemMid[0][1], &clMemIn[0]['F'-'A'], 
			&clMemMid[0][3], clCallFunc);
	fprintf(stderr, "CDF\n");	

	// AB+CD
	GPUadd(N, 2, &events[0], NULL, 0, &clMemMid[0][0], &clMemMid[0][1], &clMemMid[0][4], 
			clCallFunc);
	fprintf(stderr, "AB+CD\n");
	// ABE+CDF
	GPUadd(N, 2, &events[2], NULL, 0, &clMemMid[0][2], &clMemMid[0][3], &clMemMid[0][5], 
			clCallFunc);
	fprintf(stderr, "ABE+CDF\n");

	clFinish(clQue[0]);

	clStat = clEnqueueReadBuffer(clQue[0], clMemMid[0][4], CL_TRUE, 0, 
			sizeof(uint32_t)*N*N, hostX, 0, NULL, NULL);
	CheckFailAndExit(clStat);
	clStat = clEnqueueReadBuffer(clQue[0], clMemMid[0][5], CL_TRUE, 0, 
			sizeof(uint32_t)*N*N, hostY, 0, NULL, NULL);
	CheckFailAndExit(clStat);
	
	printf("%u\n", writeMatrixOut(N, hostX));
	printf("%u\n", writeMatrixOut(N, hostY));

	return 1;
}
void onStart(clFuncArgs) {
	int S[64];
	assert(scanf("%d", &N) == 1);
	M = 6;
	for (int i = 0; i < M; i++)
		assert(scanf("%d", &S[i]) == 1);
#pragma omp parallel for
	for (int p = 0; p < M; p++) {
		uint32_t x = 2, n = N*N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				x = (x * x + S[p] + i + j)%n;
				hostMtx[p][i*N+j] = x;
			}
		}
	}
	initAllGPU("matrix-lib.cl", clCallFunc);
	executeGPU(clCallFunc);
	destroyGPU(clCallFunc);
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
	if (signal(SIGINT, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);

	onStart(clCallFuncOuter);
	return 0;
}
