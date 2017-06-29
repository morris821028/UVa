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
static cl_context		clCtx[MAXGPU];
static cl_program 		clPrg[MAXGPU];
static cl_kernel		clKrn[MAXGPU];
static cl_command_queue	clQue[MAXGPU];
static cl_mem         	clMemOut[MAXGPU];
static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrn, clQue, clMemOut); \
	}
#define clFuncArgs cl_context clCtx[], cl_program clPrg[], cl_kernel clKrn[], \
	cl_command_queue clQue[], cl_mem clMemOut[] 
#define clCallFunc clCtx, clPrg, clKrn, clQue, clMemOut
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	if (*clMemOut)    clReleaseMemObject(*clMemOut);
	for (int i = 0; i < sizeof(clKrn)/sizeof(cl_kernel); i++) {
		if (clKrn[i])	clReleaseKernel(clKrn[i]);
	}
	for (int i = 0; i < sizeof(clQue)/sizeof(cl_command_queue); i++) {
		if (clQue[i])	clReleaseCommandQueue(clQue[i]);
	}
	for (int i = 0; i < sizeof(clPrg)/sizeof(cl_program); i++) {
		if (clPrg[i])	clReleaseProgram(clPrg[i]);
	}
	for (int i = 0; i < sizeof(clCtx)/sizeof(cl_context); i++) {
		if (clCtx[i])	clReleaseContext(clCtx[i]);
	}
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
	// -- read/generate kernel code
	static char clSrc[32767], clSrcFormat[32767];
	static size_t clSrcLen;
	{
		FILE *codefin = fopen(clSrcFile, "r");
		assert(codefin != NULL);
		clSrcLen = fread(clSrc, 1, 32767, codefin);
		assert(feof(codefin) != 0);
	}
	#pragma omp parallel for
	for (int i = 0; i < MAXGPU; i++) {
		clCtx[i] = clCreateContext(NULL, 1, clGPUID+i, NULL, NULL, &clStat);
		CheckFailAndExit(clStat);
		clQue[i] = clCreateCommandQueue(clCtx[i], clGPUID[i], 0, &clStat);
		CheckFailAndExit(clStat);
		// -- hidden process for dynamic kernel code --
		const char *clSrcPtr = clSrc;
		clPrg[i] = clCreateProgramWithSource(clCtx[i], 1, &clSrcPtr, &clSrcLen, &clStat);
		CheckFailAndExit(clStat);
		clStat = clBuildProgram(clPrg[i], 1, clGPUID+i, NULL, NULL, NULL);
		if (clStat != CL_SUCCESS) {
			size_t log_size;
			clGetProgramBuildInfo(clPrg[i], clGPUID[i],
					CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
			char *program_log = (char *) calloc(log_size+1, sizeof(char));
			clGetProgramBuildInfo(clPrg[i], clGPUID[i],
					CL_PROGRAM_BUILD_LOG, log_size+1, program_log, NULL);
			fprintf(stderr, "%s", program_log);
			free(program_log);
			CheckFailAndExit(CL_BUILD_PROGRAM_FAILURE);
			exit(1);
		}

		clKrn[i] = clCreateKernel(clPrg[i], clSrcMain[0], &clStat);
		CheckFailAndExit(clStat);
		// -- create all buffers
		cl_mem_flags clOutBuffFlag = CL_MEM_WRITE_ONLY;
		clMemOut[i] = clCreateBuffer(clCtx[i], clOutBuffFlag, sizeof(uint32_t)*MAXN/GPULOCAL/BLK, NULL, &clStat);
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
	clStat = clSetKernelArg(clKrn[DevID], 0, sizeof(cl_uint), (void *) &N);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 1, sizeof(cl_uint), (void *) &keyA);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 2, sizeof(cl_uint), (void *) &keyB);
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrn[DevID], 3, sizeof(cl_mem), (void *) &clMemOut[DevID]);
	CheckFailAndExit(clStat);


	// -- execute
	{
		N = (uint64_t) ((uint64_t)N+GPULOCAL*BLK-1)/(GPULOCAL*BLK);
		size_t globalOffset[] = {0};
		size_t globalSize[] = {N*GPULOCAL};
		size_t localSize[] = {GPULOCAL};
		clStat = clEnqueueNDRangeKernel(clQue[DevID], clKrn[DevID], 1, globalOffset,
				globalSize, localSize, 0, NULL, NULL);
		CheckFailAndExit(clStat);
	}

	// -- read back
	static __thread uint32_t sum[MAXN/GPULOCAL/BLK] = {};
	uint32_t ret = 0;
	clEnqueueReadBuffer(clQue[DevID], clMemOut[DevID], CL_TRUE, 0, sizeof(uint32_t)*N, sum, 0, NULL, NULL);
	for (int i = 0; i < N; i++)
		ret += sum[i];
	return ret;
}
int readIn(int *N, uint32_t *keyA, uint32_t *keyB) {
	if (scanf("%d %u %u", N, keyA, keyB) != 3)
		return 0;
	return 1;
}

#define MAXCASES 100000
void casesflush(int N[], uint32_t keyA[], uint32_t keyB[], int cases) {
	if (cases == 0)
		return ;
	static uint32_t ans[MAXCASES];
	omp_set_num_threads(3);
#pragma omp parallel for schedule(dynamic, 8)
	for (int i = 0; i < cases; i++) {
		int did = omp_get_thread_num();
		ans[i] = executeGPU(clCallFunc, did, 0, N[i], keyA[i], keyB[i]);
	}
	for (int i = 0; i < cases; i++)
		printf("%" PRIu32 "\n", ans[i]);
}
void onStart() {
	char kernelName[][32] = {"vecdot"};
	initAllGPU("vecdot.cl", kernelName, clCallFunc);
	int N[MAXCASES], cases = 0;
	uint32_t keyA[MAXCASES], keyB[MAXCASES];
	while (readIn(&N[cases], &keyA[cases], &keyB[cases])) {
		cases++;
		if (cases == MAXCASES) {
			casesflush(N, keyA, keyB, cases);
			cases = 0;
		}
	}
	casesflush(N, keyA, keyB, cases);
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
