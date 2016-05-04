#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#include "utils.h"
#include <omp.h>
#define MAXGPU 1
#define MAXN 16777216
#define GPULOCAL 64
uint32_t  hostA[MAXN], hostB[MAXN], hostC[MAXN/GPULOCAL];

int N;
char clSrcFormat[1024] = ""; 
char clSrc[1024] = "";
char clSrcMain[1024] = "vecdot";
// -- start working with OpenCL
cl_context             clCtx;
cl_program             clPrg;
cl_kernel              clKrn;
cl_command_queue     clQue;
cl_mem         clMemIn1, clMemIn2, clMemOut;

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error: Line %u in file %s\n\n", __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrn, clQue, clMemIn1, clMemIn2, clMemOut); \
	}
#define clFuncArgs cl_context *clCtx, cl_program *clPrg, cl_kernel *clKrn, \
	cl_command_queue *clQue, cl_mem *clMemIn1, cl_mem *clMemIn2, \
cl_mem *clMemOut 
#define clCallFunc &clCtx, &clPrg, &clKrn, &clQue, &clMemIn1, &clMemIn2, &clMemOut
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	if (*clMemOut)    clReleaseMemObject(*clMemOut);
	if (*clMemIn2)    clReleaseMemObject(*clMemIn2);
	if (*clMemIn1)    clReleaseMemObject(*clMemIn1);
	if (*clKrn)	clReleaseKernel(*clKrn);
	if (*clPrg)	clReleaseProgram(*clPrg);
	if (*clQue)	clReleaseCommandQueue(*clQue);
	if (*clCtx)	clReleaseContext(*clCtx);
	exit(0);
}
int initAllGPU(char fileName[], clFuncArgs) {
	// -- generate kernel code
	FILE *codefin = fopen(fileName, "r");
	assert(codefin != NULL);
	size_t clSrcLen = fread(clSrc, 1, 1024, codefin);

	cl_int                 clStat;
	cl_uint             clPlatN, clGPUN;
	cl_platform_id         clPlatID;
	cl_device_id         clGPUID[MAXGPU];
	const char             *clSrcPtr = clSrc;

	// -- basic OpenCL setup
	clGetPlatformIDs(1, &clPlatID, &clPlatN);
	clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, MAXGPU, clGPUID, NULL);
	*clCtx = clCreateContext(NULL, 1, clGPUID, NULL, NULL, &clStat);
	CheckFailAndExit(clStat);
	*clQue = clCreateCommandQueue(*clCtx, clGPUID[0], 0, &clStat);
	CheckFailAndExit(clStat);
	*clPrg = clCreateProgramWithSource(*clCtx, 1, &clSrcPtr, &clSrcLen, &clStat);
	CheckFailAndExit(clStat);
	clStat = clBuildProgram(*clPrg, 1, clGPUID, NULL, NULL, NULL);
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
	*clKrn = clCreateKernel(*clPrg, clSrcMain, &clStat);
	CheckFailAndExit(clStat);
	// -- create all buffers
	cl_mem_flags clInBuffFlag = CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR;
	cl_mem_flags clOutBuffFlag = CL_MEM_WRITE_ONLY;
	*clMemIn1 = clCreateBuffer(*clCtx, clInBuffFlag, sizeof(uint32_t)*MAXN, 
			hostA, &clStat);
	CheckFailAndExit(clStat);
	*clMemIn2 = clCreateBuffer(*clCtx, clInBuffFlag, sizeof(uint32_t)*MAXN,
			hostB, &clStat);
	CheckFailAndExit(clStat);
	*clMemOut = clCreateBuffer(*clCtx, clOutBuffFlag, sizeof(uint32_t)*MAXN/GPULOCAL,
			hostC, &clStat);
	CheckFailAndExit(clStat);

	// -- set argument to kernel
	clStat = clSetKernelArg(*clKrn, 0, sizeof(cl_mem), (void *) clMemIn1);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(*clKrn, 1, sizeof(cl_mem), (void *) clMemIn2);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(*clKrn, 2, sizeof(cl_mem), (void *) clMemOut);
	CheckFailAndExit(clStat);

	return 1;
}
int executeGPU(clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {N};
	size_t localSize[] = {GPULOCAL};
	
	// -- write into
	clStat = clEnqueueWriteBuffer(*clQue, *clMemIn1, CL_TRUE, 0, sizeof(uint32_t)*N,
			hostA, 0, NULL, NULL);
	CheckFailAndExit(clStat);
	clStat = clEnqueueWriteBuffer(*clQue, *clMemIn2, CL_TRUE, 0, sizeof(uint32_t)*N,
			hostB, 0, NULL, NULL);
	CheckFailAndExit(clStat);

	// -- execute
	clStat = clEnqueueNDRangeKernel(*clQue, *clKrn, 1, globalOffset,
			globalSize, localSize, 0, NULL, NULL);
	CheckFailAndExit(clStat);
	
	// -- read back
	clEnqueueReadBuffer(*clQue, *clMemOut, CL_TRUE, 0, sizeof(uint32_t)*N/GPULOCAL, 
			hostC, 0, NULL, NULL);

	return 1;
}
int readIn() {
	uint32_t c1, c2;
	int has = 0;
	if (scanf("%d %u %u", &N, &c1, &c2) != 3)
		return 0;
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		hostA[i] = encrypt(i, c1);
		hostB[i] = encrypt(i, c2);
	}
	// -- padding
	while (N%GPULOCAL)
		hostA[N] = hostB[N] = 0, N++;
	return 1;
}
void writeOut() {
	uint32_t sum = 0;
	omp_set_num_threads(4);
#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < N/GPULOCAL; i++)
		sum += hostC[i];
	printf("%u\n", sum);
}
void onStart() {
	initAllGPU("vecdot.cl", clCallFunc);
	while (readIn()) {
		executeGPU(clCallFunc);
		writeOut();
	}
	destroyGPU(clCallFunc);
}

void sigHandler(int signo) {
	printf("God Bless Me\n");
	destroyGPU(clCallFunc);
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

	onStart();
	return 0;
}
