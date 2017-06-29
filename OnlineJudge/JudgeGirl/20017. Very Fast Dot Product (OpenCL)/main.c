#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#define MAXGPU 1
#define MAXN (1<<26)
#define GPULOCAL 256
// -- start working with OpenCL
static cl_context		clCtx;
static cl_program 		clPrg;
static cl_kernel		clKrn[2];
static cl_command_queue	clQue;
static cl_mem         	clMemOut;

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrn, clQue, clMemOut); \
	}
#define clFuncArgs cl_context *clCtx, cl_program *clPrg, cl_kernel clKrn[], \
	cl_command_queue *clQue, cl_mem *clMemOut  
#define clCallFunc &clCtx, &clPrg, clKrn, &clQue, &clMemOut
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	if (*clMemOut)    clReleaseMemObject(*clMemOut);
	for (int i = 0; i < sizeof(clKrn)/sizeof(cl_kernel); i++) {
		if (clKrn[i])	
			clReleaseKernel(clKrn[i]);
	}
	if (*clPrg)	clReleaseProgram(*clPrg);
	if (*clQue)	clReleaseCommandQueue(*clQue);
	if (*clCtx)	clReleaseContext(*clCtx);
	exit(0);
}
int initAllGPU(char clSrcFile[], char clSrcMain[][32], clFuncArgs) {
	cl_int			clStat;
	cl_uint			clPlatN, clGPUN;
	cl_platform_id	clPlatID;
	cl_device_id	clGPUID[MAXGPU];

	// -- basic OpenCL setup
	clStat = clGetPlatformIDs(1, &clPlatID, &clPlatN);
	CheckFailAndExit(clStat);
	clStat = clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, MAXGPU, clGPUID, &clGPUN);
	CheckFailAndExit(clStat);
	*clCtx = clCreateContext(NULL, 1, clGPUID, NULL, NULL, &clStat);
	CheckFailAndExit(clStat);
	*clQue = clCreateCommandQueue(*clCtx, clGPUID[0], 0, &clStat);
	CheckFailAndExit(clStat);

	// -- read/generate kernel code
	{
		static char clSrc[32767], clSrcFormat[32767];
		FILE *codefin = fopen(clSrcFile, "r");
		assert(codefin != NULL);
		size_t clSrcLen = fread(clSrc, 1, 32767, codefin);
		assert(feof(codefin) != 0);
		// -- hidden process for dynamic kernel code --
		const char *clSrcPtr = clSrc;
		*clPrg = clCreateProgramWithSource(*clCtx, 1, &clSrcPtr, &clSrcLen, &clStat);
		CheckFailAndExit(clStat);
	}
	clStat = clBuildProgram(*clPrg, 1, clGPUID, NULL, NULL, NULL);
	if (clStat != CL_SUCCESS) {
		size_t log_size;
		clGetProgramBuildInfo(*clPrg, clGPUID[0],
				CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *program_log = (char *) calloc(log_size+1, sizeof(char));
		clGetProgramBuildInfo(*clPrg, clGPUID[0],
				CL_PROGRAM_BUILD_LOG, log_size+1, program_log, NULL);
		fprintf(stderr, "%s", program_log);
		free(program_log);
		CheckFailAndExit(CL_BUILD_PROGRAM_FAILURE);
		exit(1);
	}
	clKrn[0] = clCreateKernel(*clPrg, clSrcMain[0], &clStat);
	CheckFailAndExit(clStat);
	clKrn[1] = clCreateKernel(*clPrg, clSrcMain[1], &clStat);
	CheckFailAndExit(clStat);

	// -- create all buffers
	cl_mem_flags clOutBuffFlag = CL_MEM_READ_WRITE;
	*clMemOut = clCreateBuffer(*clCtx, clOutBuffFlag, sizeof(uint32_t)*MAXN/256/GPULOCAL,
			NULL, &clStat);
	CheckFailAndExit(clStat);

	return 1;
}
// -- end working with OpenCL

int executeGPU(clFuncArgs, int N, uint32_t keyA, uint32_t keyB) {
	cl_int clStat;

	// -- set argument to kernel
	clStat = clSetKernelArg(clKrn[0], 0, sizeof(cl_uint), (void *) &N);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[0], 1, sizeof(cl_uint), (void *) &keyA);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[0], 2, sizeof(cl_uint), (void *) &keyB);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[0], 3, sizeof(cl_mem), (void *) clMemOut);
	CheckFailAndExit(clStat);

	// -- execute
	{
		static const int BLK = 256;
		N = (N+GPULOCAL*BLK-1)/(GPULOCAL*BLK)*GPULOCAL;
		size_t globalOffset[] = {0};
		size_t globalSize[] = {N};
		size_t localSize[] = {GPULOCAL};

		clStat = clEnqueueNDRangeKernel(*clQue, clKrn[0], 1, globalOffset,
				globalSize, localSize, 0, NULL, NULL);
		CheckFailAndExit(clStat);
	}

	// -- execute reduction
	{
		N = N/GPULOCAL;
		clStat = clSetKernelArg(clKrn[1], 0, sizeof(cl_uint), (void *) &N);
		CheckFailAndExit(clStat);
		clStat = clSetKernelArg(clKrn[1], 1, sizeof(cl_mem), (void *) clMemOut);
		CheckFailAndExit(clStat);
		size_t globalOffset[] = {0};
		size_t globalSize[] = {1024};
		size_t localSize[] = {1024};
		assert(N <= localSize[0]);
		clStat = clEnqueueNDRangeKernel(*clQue, clKrn[1], 1, globalOffset,
				globalSize, localSize, 0, NULL, NULL);
		CheckFailAndExit(clStat);
	}

	// -- read back
	uint32_t sum;
	clEnqueueReadBuffer(*clQue, *clMemOut, CL_TRUE, 0, sizeof(uint32_t), &sum, 0, NULL, NULL);

	printf("%u\n", sum);

	return 1;
}
int readIn(int *N, uint32_t *keyA, uint32_t *keyB) {
	int has = 0;
	if (scanf("%d %u %u", N, keyA, keyB) != 3)
		return 0;
	return 1;
}
void onStart() {
	char kernelName[][32] = {"vecdot", "reduction"};
	initAllGPU("vecdot.cl", kernelName, clCallFunc);
	int N;
	uint32_t keyA, keyB;
	while (readIn(&N, &keyA, &keyB))
		executeGPU(clCallFunc, N, keyA, keyB);
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
	if (signal(SIGINT, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);
	//	freopen("1.in", "r", stdin);
	onStart();
	return 0;
}

