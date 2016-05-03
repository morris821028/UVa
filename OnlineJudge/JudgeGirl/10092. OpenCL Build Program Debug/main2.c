#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <CL/cl.h>

#define MAXGPU 1
#define MAXN 2048

int N = MAXN;
char clSrc[1024] = "";
char clSrcMain[1024] = "notused";
// -- start working with OpenCL
cl_context             clCtx;
cl_program             clPrg;

#define clCallFunc &clCtx, &clPrg
#define clFuncArgs cl_context *clCtx, cl_program *clPrg
#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error: Line %u in file %s\n\n", __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg); \
	}
#define clPrint(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
void destroyGPU(clFuncArgs) {
	fprintf(stderr, "Starting Cleanup ...\n\n");
	if (*clCtx)	clReleaseContext(*clCtx);
	if (*clPrg)	clReleaseProgram(*clPrg);
	exit(0);
}
void clCompile(char fileName[], clFuncArgs) {
	FILE *codefin = fopen(fileName, "r");
	assert(codefin != NULL);
	size_t clSrcLen = fread(clSrc, 1, 1024, codefin);
	fclose(codefin);
	cl_int				clStat;
	cl_uint				clPlatN, clGPUN;
	cl_platform_id		clPlatID;
	cl_device_id		clGPUID[MAXGPU];
	const char			*clSrcPtr = clSrc;

	// -- basic OpenCL setup
	clGetPlatformIDs(1, &clPlatID, &clPlatN);
	clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, MAXGPU, clGPUID, &clGPUN);
	*clCtx = clCreateContext(NULL, 1, clGPUID, NULL, NULL, &clStat);
	CheckFailAndExit(clStat);
	*clPrg = clCreateProgramWithSource(*clCtx, 1, &clSrcPtr, &clSrcLen, &clStat);
	CheckFailAndExit(clStat);
	clStat = clBuildProgram(*clPrg, 1, clGPUID, NULL, NULL, NULL);
	if (clStat != CL_SUCCESS) {
		static char program_log[32767];
		clGetProgramBuildInfo(*clPrg, clGPUID[0],
				CL_PROGRAM_BUILD_LOG, sizeof(program_log), program_log, NULL);
		printf("%s", program_log);
		CheckFailAndExit(CL_BUILD_PROGRAM_FAILURE);
	}
}

int main() {
	char fileName[128];
	assert(scanf("%s", fileName) == 1);
	clCompile(fileName, clCallFunc);
	// Compile Success
	destroyGPU(clCallFunc);
	return 0;
}
