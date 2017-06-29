#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <omp.h>
#include <CL/cl.h>
#define MAXGPU 3
#define MAXN (1U<<30)
#define BLK 256
#define GPULOCAL 256
// -- start working with OpenCL
static cl_context		clCtx;
static cl_program 		clPrg;
static cl_kernel		clKrn[MAXGPU];
static cl_command_queue	clQue[MAXGPU];
static cl_mem         	clMemOut[MAXGPU];

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrn, clQue, clMemOut); \
	}
#define clFuncArgs cl_context *clCtx, cl_program *clPrg, cl_kernel clKrn[], \
	cl_command_queue clQue[], cl_mem clMemOut[] 
#define clCallFunc &clCtx, &clPrg, clKrn, clQue, clMemOut
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	if (*clMemOut)    clReleaseMemObject(*clMemOut);
	for (int i = 0; i < sizeof(clKrn)/sizeof(cl_kernel); i++) {
		if (clKrn[i])	
			clReleaseKernel(clKrn[i]);
	}
	for (int i = 0; i < sizeof(clQue)/sizeof(cl_command_queue); i++) {
		if (clQue[i])	
			clReleaseCommandQueue(clQue[i]);
	}

	if (*clPrg)	clReleaseProgram(*clPrg);
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
	*clCtx = clCreateContext(NULL, 3, clGPUID, NULL, NULL, &clStat);
	CheckFailAndExit(clStat);
	for (int i = 0; i < 3; i++)
		clQue[i] = clCreateCommandQueue(*clCtx, clGPUID[i], 0, &clStat);
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
	clStat = clBuildProgram(*clPrg, 3, clGPUID, NULL, NULL, NULL);
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

	for (int i = 0; i < 3; i++) {
		clKrn[i] = clCreateKernel(*clPrg, clSrcMain[0], &clStat);
		CheckFailAndExit(clStat);
	}

	// -- create all buffers
	cl_mem_flags clOutBuffFlag = CL_MEM_WRITE_ONLY;
	for (int i = 0; i < 3; i++) {
		clMemOut[i] = clCreateBuffer(*clCtx, clOutBuffFlag, sizeof(uint32_t)*MAXN/GPULOCAL/BLK, NULL, &clStat);
		CheckFailAndExit(clStat);
	}
	return 1;
}
// -- end working with OpenCL

uint32_t executeGPU(clFuncArgs, int DevID, int OFF, int N, uint32_t keyA, uint32_t keyB) {
	if (N <= 0)
		return 0;
	cl_int clStat;

	// -- set argument to kernel
	clStat = clSetKernelArg(clKrn[DevID], 0, sizeof(cl_uint), (void *) &OFF);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 1, sizeof(cl_uint), (void *) &N);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 2, sizeof(cl_uint), (void *) &keyA);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 3, sizeof(cl_uint), (void *) &keyB);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 4, sizeof(cl_mem), (void *) &clMemOut[DevID]);
	CheckFailAndExit(clStat);


	// -- execute
	{
		N = (uint64_t) ((uint64_t)N+GPULOCAL*BLK-1)/(GPULOCAL*BLK);
		size_t globalOffset[] = {0};
		size_t globalSize[] = {N*GPULOCAL};
		size_t localSize[] = {GPULOCAL};
		const int ZERO = 0;
		clStat = clEnqueueNDRangeKernel(clQue[DevID], clKrn[DevID], 1, globalOffset,
				globalSize, localSize, 0, NULL, NULL);
		CheckFailAndExit(clStat);
	}

	// -- read back
	uint32_t sum[MAXN/GPULOCAL/BLK] = {};
	uint32_t ret = 0;
	assert(N <= MAXN/GPULOCAL/BLK);
	clEnqueueReadBuffer(clQue[DevID], clMemOut[DevID], CL_TRUE, 0, sizeof(uint32_t)*N, &sum, 0, NULL, NULL);
//	omp_set_num_threads(4);
//	#pragma omp parallel for reduction(+:ret)
	for (int i = 0; i < N; i++)
		ret += sum[i];

	return ret;
}
int readIn(int *N, uint32_t *keyA, uint32_t *keyB) {
	int has = 0;
	if (scanf("%d %u %u", N, keyA, keyB) != 3)
		return 0;
	return 1;
}
int solver(int devID, int *cases, uint32_t ansQue[]) {
	int N, f, cid;
	uint32_t keyA, keyB;
	while (1) {
#pragma omp critical
		{
			f = readIn(&N, &keyA, &keyB);
			cid = *cases;
			*cases += f;
		}
		if (f == 0)
			break;
		ansQue[cid] = executeGPU(clCallFunc, devID, 0, N, keyA, keyB);
	}
	return 0;
}
void onStart() {
	char kernelName[][32] = {"vecdot"};
	initAllGPU("vecdot.cl", kernelName, clCallFunc);
	static uint32_t ansQue[131072];
	int cases = 0;
#pragma omp parallel sections
	{
#pragma omp section
		{
			solver(0, &cases, ansQue);
		}
#pragma omp section
		{
			solver(1, &cases, ansQue);
		}
#pragma omp section
		{
			solver(2, &cases, ansQue);
		}
	}
	for (int i = 0; i < cases; i++)
		printf("%" PRIu32 "\n", ansQue[i]);
	destroyGPU(clCallFunc);
}

void sigHandler(int signo) {
	printf("God Bless Me\n");
	destroyGPU(clCallFunc);
	exit(0);
}
int main(int argc, char *argv[]) {
	onStart();
	return 0;
}
