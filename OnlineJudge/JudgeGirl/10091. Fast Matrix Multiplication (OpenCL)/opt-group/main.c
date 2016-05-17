#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
 
#define MAXGPU 1
#define MAXN 1024
uint32_t  hostA[MAXN*MAXN], hostB[MAXN*MAXN], hostC[MAXN*MAXN];
 
int N = MAXN;
char clSrcFormat[1024]; 
char clSrc[1024] = "";
char clSrcMain[1024] = "matrixMul";
// -- start working with OpenCL
cl_context             clCtx;
cl_program             clPrg;
cl_kernel              clKrn;
cl_command_queue     clQue;
cl_mem         clMemIn1, clMemIn2, clMemOut;
 
#define CheckFailAndExit(state) \
    if (state != CL_SUCCESS) { \
        printf("Error: Line %u in file %s\n\n", __LINE__, __FILE__), \
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
    if (*clKrn)    clReleaseKernel(*clKrn);
    if (*clPrg) clReleaseProgram(*clPrg);
    if (*clQue)    clReleaseCommandQueue(*clQue);
    if (*clCtx)    clReleaseContext(*clCtx);
    exit(0);
}
int initAllGPU(char fileName[], clFuncArgs) {
    // -- generate kernel code
    FILE *codefin = fopen(fileName, "r");
    assert(codefin != NULL);
    size_t clSrcLen = fread(clSrcFormat, 1, 1024, codefin);
    sprintf(clSrc, clSrcFormat, N);
    fclose(codefin);
    cl_int                 clStat;
    cl_uint             clPlatN, clGPUN;
    cl_platform_id         clPlatID;
    cl_device_id         clGPUID[MAXGPU];
    const char             *clSrcPtr = clSrc;
    // -- basic OpenCL setup
    clGetPlatformIDs(1, &clPlatID, &clPlatN);
    clGetDeviceIDs(clPlatID, CL_DEVICE_TYPE_GPU, MAXGPU, clGPUID, &clGPUN);
    *clCtx = clCreateContext(NULL, 1, clGPUID, NULL, NULL, &clStat);
    CheckFailAndExit(clStat);
    *clQue = clCreateCommandQueue(*clCtx, clGPUID[0], 0, &clStat);
    CheckFailAndExit(clStat);
    *clPrg = clCreateProgramWithSource(*clCtx, 1, &clSrcPtr, &clSrcLen, &clStat);
    CheckFailAndExit(clStat);
    clStat = clBuildProgram(*clPrg, 1, clGPUID, NULL, NULL, NULL);
    if (clStat != CL_SUCCESS) {
        printf("Error in clBuildProgram, Line %u in file %s\n\n", __LINE__, __FILE__);
        size_t log_size;
        clGetProgramBuildInfo(*clPrg, clGPUID[0], CL_PROGRAM_BUILD_STATUS,
                sizeof(cl_build_status), &clStat, NULL);
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
    *clMemIn1 = clCreateBuffer(*clCtx, clInBuffFlag, sizeof(uint32_t)*N*N, 
            hostA, &clStat);
    CheckFailAndExit(clStat);
    *clMemIn2 = clCreateBuffer(*clCtx, clInBuffFlag, sizeof(uint32_t)*N*N,
            hostB, &clStat);
    CheckFailAndExit(clStat);
    *clMemOut = clCreateBuffer(*clCtx, clOutBuffFlag, sizeof(uint32_t)*N*N,
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
int min(int x, int y) {
    return x < y ? x : y;
}
int executeGPU(clFuncArgs) {
    cl_int clStat;
    size_t globalOffset[] = {0, 0};
    size_t globalSize[] = {N};
    size_t localSize[] = {min(N, 64)};
    clStat = clEnqueueNDRangeKernel(*clQue, *clKrn, 1, globalOffset,
            globalSize, localSize, 0, NULL, NULL);
    CheckFailAndExit(clStat);
    clFinish(*clQue);
    // -- read back
    clEnqueueReadBuffer(*clQue, *clMemOut, CL_TRUE, 0, sizeof(uint32_t)*N*N, 
            hostC, 0, NULL, NULL);
    return 1;
}
void readIn() {
    uint32_t c1, c2;
    assert(scanf("%d %u %u", &N, &c1, &c2) == 3);
    uint32_t x = 2, n = N*N;
    x = 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c1 + i + j)&(n-1);
            hostA[i*N+j] = x;
        }
    }
    x = 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c2 + i + j)&(n-1);
            hostB[i*N+j] = x;
        }
    }
}
void writeOut() {
    uint32_t h = 0;
    uint32_t *Cend = hostC + N*N, *C = hostC;
    for (; C != Cend; C++)
        h = (h + *C) * 2654435761LU;
    printf("%u\n", h);
}
void onStart() {
    readIn();
    initAllGPU("matrixmul.cl", clCallFunc);
    executeGPU(clCallFunc);
    writeOut();
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
