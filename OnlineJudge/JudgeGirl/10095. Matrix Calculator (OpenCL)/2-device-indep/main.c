#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>
#include <omp.h>
#define MAXGPU 2
#define MAXN 1024
#define MAXM 26
#define GPULOCAL 64
#define MAXMID 20
uint32_t	hostMtx[MAXM][MAXN*MAXN];

int N, binN, M, Q;
char expr[1024];
char clSrcFormat[32767] = ""; 
char clSrc[32767] = "";
// -- start working with OpenCL
const int clNeedDevCnt = 2;
cl_context				clCtx[2];
cl_program				clPrg[2];
cl_kernel				clKrnAdd[2], clKrnMul[2];
cl_command_queue		clQue[2];
cl_mem					clMemIn[2][MAXM], clMemMid[2][MAXM*2];
typedef struct Node {
	struct Node *l, *r;
	int opcode;
	uint32_t *hostV;
	cl_mem	clV;
	cl_event event, *waitEvents;
	int waitEventsN;
	int pid, mid;
	long long h;
} Node;

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) { \
		fprintf(stderr, "Error %d: Line %u in file %s\n\n", status, __LINE__, __FILE__), \
		destroyGPU(clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn); \
	}
#define clFuncArgs cl_context clCtx[], cl_program clPrg[], cl_kernel clKrnAdd[], \
	cl_kernel clKrnMul[], cl_command_queue clQue[], cl_mem clMemIn[][MAXM]
#define clCallFunc clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn
#define clCallFuncOuter clCtx, clPrg, clKrnAdd, clKrnMul, clQue, clMemIn
void assignGPU(Node *u, int gpuIdx) {
	if (u == NULL)	return ;
	if (u->l == NULL) {
		u->hostV = hostMtx[u->mid];
		u->clV = clMemIn[gpuIdx][u->mid];
		return ;
	}
	assignGPU(u->l, gpuIdx);
	assignGPU(u->r, gpuIdx);
}
Node* parseExpr(int l, int r, char expr[], int procId, clFuncArgs) {
	cl_int clStat;
	Node *u = (Node *) calloc(1, sizeof(Node));
	u->pid = procId;
	if (l == r) {
		int idx = expr[l] - 'A';
		u->hostV = hostMtx[idx];
		u->mid = idx;
		u->h = 0;
		return u;
	}
	int cnt = 0;
	for (int i = l; i <= r; i++) {
		if (expr[i] == '(') {
			cnt++;
		} else if (expr[i] == ')') {
			cnt--;
		} else if (expr[i] == '+' && cnt == 0) {
			u->l = parseExpr(l, i-1, expr, procId, clCallFunc);
			u->r = parseExpr(i+1, r, expr, procId, clCallFunc);
			u->opcode = '+';
			u->h = u->l->h + u->r->h + N;
			return u;
		}
	}

	for (int i = l; i <= r; i++) {
		if (expr[i] == '(') {
			if (cnt == 0 && i != l) {
				u->l = parseExpr(l, i-1, expr, procId, clCallFunc);
				u->r = parseExpr(i, r, expr, procId, clCallFunc);
				u->opcode = '*';
				u->h = u->l->h + u->r->h + N*N;
				return u;
			}
			cnt++;
		} else if (expr[i] == ')') {
			cnt--;
		} else if (expr[i] >= 'A' && expr[i] <= 'Z' && cnt == 0 && i != l) {
			u->l = parseExpr(l, i-1, expr, procId, clCallFunc);
			u->r = parseExpr(i, r, expr, procId, clCallFunc);
			u->opcode = '*';
			u->h = u->l->h + u->r->h + N*N;
			return u;
		}
	}
	free(u);
	return parseExpr(l+1, r-1, expr, procId, clCallFunc);
}
uint32_t writeMatrixOut(int N, uint32_t *A) {
	uint32_t h = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			h = (h + A[i*binN + j]) * 2654435761LU;
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
		if (clCtx[i])	
			clReleaseContext(clCtx[i]);
	}
	exit(0);
}
int initAllGPU(char fileName[], clFuncArgs) {
	// -- generate kernel code
	FILE *codefin = fopen(fileName, "r");
	assert(codefin != NULL);
	assert(fread(clSrcFormat, 1, 32767, codefin) < 32767);
	sprintf(clSrc, clSrcFormat, binN);
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
				CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &clStat);
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
		clKrnAdd[i] = clCreateKernel(clPrg[i], "matrixAdd", &clStat);
		CheckFailAndExit(clStat);
		clKrnMul[i] = clCreateKernel(clPrg[i], "matrixMul", &clStat);
		CheckFailAndExit(clStat);
	}

	// -- create all buffers
	cl_mem_flags clInBuffFlag = CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR;
	for (int d = 0; d < clNeedDevCnt; d++) {
		for (int i = 0; i < M; i++) {
			clMemIn[d][i] = clCreateBuffer(clCtx[d], clInBuffFlag, sizeof(uint32_t)*binN*binN,
					hostMtx[i], &clStat);
			CheckFailAndExit(clStat);
		}
	}
	for (int d = 0; d < clNeedDevCnt; d++) {
		for (int i = 0; i < MAXMID; i++) {
			clMemMid[d][i] = clCreateBuffer(clCtx[d], CL_MEM_READ_WRITE, 
					sizeof(uint32_t)*binN*binN, NULL, &clStat);
			CheckFailAndExit(clStat);
		}
	}

	return 1;
}
void GPUmultiply(int N, Node *U, Node *L, Node *R, int devIdx, clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {binN};
	size_t localSize[] = {GPULOCAL};

	// -- set argument to kernel
	clStat = clSetKernelArg(clKrnMul[devIdx], 0, sizeof(cl_mem), &(L->clV));
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnMul[devIdx], 1, sizeof(cl_mem), &(R->clV));
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnMul[devIdx], 2, sizeof(cl_mem), &(U->clV));
	CheckFailAndExit(clStat);

	// -- find wait events
	int waitN = 0, waitCnt = 0;
	if (L->event)	waitCnt++;
	if (R->event)	waitCnt++;
	cl_event *events = (cl_event*) malloc(sizeof(cl_event) * waitCnt);
	if (L->event)	events[waitN++] = L->event;
	if (R->event)	events[waitN++]	= R->event;
	U->waitEvents = events, U->waitEventsN = waitCnt;
	// -- execute
	clStat = clEnqueueNDRangeKernel(clQue[devIdx], clKrnMul[devIdx], 1, globalOffset,
			globalSize, localSize, U->waitEventsN, U->waitEvents, &(U->event) );
	CheckFailAndExit(clStat);
}
void GPUadd(int N, Node *U, Node *L, Node *R, int devIdx, clFuncArgs) {
	cl_int clStat;
	size_t globalOffset[] = {0};
	size_t globalSize[] = {binN*binN};
	size_t localSize[] = {1};

	// -- set argument to kernel	
	clStat = clSetKernelArg(clKrnAdd[devIdx], 0, sizeof(cl_mem), &(L->clV));
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnAdd[devIdx], 1, sizeof(cl_mem), &(R->clV));
	CheckFailAndExit(clStat);
	clStat = clSetKernelArg(clKrnAdd[devIdx], 2, sizeof(cl_mem), &(U->clV));
	CheckFailAndExit(clStat);

	// -- find wait events
	int waitN = 0, waitCnt = 0;
	if (L->event)	waitCnt++;
	if (R->event)	waitCnt++;
	cl_event *events = (cl_event*) malloc(sizeof(cl_event) * waitCnt);
	if (L->event)	events[waitN++] = L->event;
	if (R->event)	events[waitN++]	= R->event;
	U->waitEvents = events, U->waitEventsN = waitCnt;
	// -- execute
	clStat = clEnqueueNDRangeKernel(clQue[devIdx], clKrnAdd[devIdx], 1, globalOffset,
			globalSize, localSize, U->waitEventsN, U->waitEvents, &(U->event) );
	CheckFailAndExit(clStat);
}
int executeGPU(Node *workQue[][128], int workQueSz[], uint32_t resultBuff[], clFuncArgs) {
	cl_int clStat;
	Node* nodes[2][128];
	int offset[2] = {};
	#pragma omp parallel for
	for (int p = 0; p < clNeedDevCnt; p++) {
		for (int q = 0; q < workQueSz[p]; q++) {
			// -- flatten binary tree
			offset[p] = 0;
			nodes[p][offset[p]++] = workQue[p][q];
			for (int i = 0; i < offset[p]; i++) {
				Node *u = nodes[p][i];
				if (u->l != NULL)
					nodes[p][offset[p]++] = u->l;
				if (u->r != NULL)
					nodes[p][offset[p]++] = u->r;
			}

			// -- execute in order
			int reuseId = 0;
			for (int i = offset[p]-1; i >= 0; i--) {
				Node *u = nodes[p][i];
				if (u->l == NULL)	// is leaf
					continue;
				u->clV = clMemMid[p][reuseId++];
				if (u->opcode == '*')
					GPUmultiply(N, u, u->l, u->r, p, clCallFunc);	
				else
					GPUadd(N, u, u->l, u->r, p, clCallFunc);
			}
			clFlush(clQue[p]);
			clFinish(clQue[p]);
			nodes[p][0]->hostV = (uint32_t *) malloc(sizeof(uint32_t)*binN*binN);
			int waitN = nodes[p][0]->event != NULL;
			clStat = clEnqueueReadBuffer(clQue[p], nodes[p][0]->clV, CL_TRUE, 0, 
					sizeof(uint32_t)*binN*binN, nodes[p][0]->hostV, waitN, 
					waitN ? &(nodes[p][0]->event): NULL, NULL);
			uint32_t ret = writeMatrixOut(N, nodes[p][0]->hostV);
			resultBuff[nodes[p][0]->pid] = ret;
			// -- free inner node buffer
			for (int i = 0; i < offset[p]; i++) {
				Node *u = nodes[p][i];
				if (u->l != NULL && u->hostV)
					free(u->hostV);
				if (u->l != NULL && u->event)
					clReleaseEvent(u->event);
				if (u->l != NULL && u->waitEvents)
					free(u->waitEvents);
				free(u);
			}

		}
	}
	return 1;
}
void CPUmultiply(int N, uint32_t *A, uint32_t *B, uint32_t *C) {
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			uint32_t sum = 0;
			for (int k = 0; k < N; k++)
				sum += A[i*binN+k] * B[k*binN+j];
			C[i*binN+j] = sum;
		}
	}
}
void CPUadd(int N, uint32_t *A, uint32_t *B, uint32_t *C) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i*binN+j] = A[i*binN+j] + B[i*binN+j];
		}
	}
}
int executeCPU(Node *root) {
	// -- flatten binary tree
	Node* nodes[128];
	int offset = 0;

	nodes[offset++] = root;
	for (int i = 0; i < offset; i++) {
		Node *u = nodes[i];
		if (u->l != NULL)
			nodes[offset++] = u->l;
		if (u->r != NULL)
			nodes[offset++] = u->r;
	}

	for (int i = offset-1; i >= 0; i--) {
		Node *u = nodes[i];
		if (u->l == NULL)	// is leaf
			continue;
		u->hostV = (uint32_t *) calloc(1, sizeof(uint32_t)*binN*binN);
		if (u->opcode == '*')
			CPUmultiply(N, u->l->hostV, u->r->hostV, u->hostV);	
		else
			CPUadd(N, u->l->hostV, u->r->hostV, u->hostV);
		// -- free inner node buffer
		if (u->l->l != NULL)
			free(u->l->hostV), u->l->hostV = NULL;
		if (u->r->l != NULL)
			free(u->r->hostV), u->r->hostV = NULL;
	}
	/*
	   for (int k = 0; k < M; k++) {
	   printf("=== Matrix %c ===\n", k + 'A');
	   for (int i = 0; i < N; i++) {
	   for (int j = 0; j < N; j++)
	   printf("%u ", hostMtx[k][i*N+j]);
	   puts("");
	   }
	   }
	*/
/*	puts("=== final");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%u ", nodes[0]->hostV[i*binN+j]);
		puts("");
	}
*/

	uint32_t ret = writeMatrixOut(N, nodes[0]->hostV);
	printf("%u\n", ret);

	for (int i = 0; i < offset; i++) {
		Node *u = nodes[i];
		if (u->l != NULL && u->hostV)
			free(u->hostV);
		free(u);
	}
}
int readIn() {
	if (scanf("%s", expr) != 1)
		return 0;
	return 1;
}
int balance_cmp(const void *a, const void *b) {
	Node *x = *(Node **) a;
	Node *y = *(Node **) b;
	if (x->h == y->h)	return 0;
	if (x->h < y->h)	return 1;
	return -1;
}
void onStart(clFuncArgs) {
	int S[64];
	M = 6;
	assert(scanf("%d", &N) == 1);
	binN = N;
	while (binN % GPULOCAL)
		binN++;
	for (int i = 0; i < M; i++)
		assert(scanf("%d", &S[i]) == 1);
#pragma omp parallel for
	for (int p = 0; p < M; p++) {
		uint32_t x = 2, n = N*N;
		memset(hostMtx[p], 0, sizeof(uint32_t)*binN*binN);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				x = (x * x + S[p] + i + j)%n;
				hostMtx[p][i*binN+j] = x;
			}
		}
	}
	initAllGPU("matrix-lib.cl", clCallFunc);

	Node *procBuff[128];
	Q = 2;
	for (int i = 0; i < Q; i++) {
		if (i == 0)	strcpy(expr, "AB+CD");
		else		strcpy(expr, "ABE+CDF");
		int expr_len = strlen(expr);
		procBuff[i] = parseExpr(0, expr_len-1, expr, i, clCallFunc);
	}
	/*
	   for (int i = 0; i < Q; i++)
	   executeCPU(procBuff[i]);
	   return ; 
	 */


	qsort(procBuff, Q, sizeof(Node*), balance_cmp);
	long long workload[16] = {};
	int workQueSz[2] = {};
	uint32_t resultBuff[128];
	Node *workQue[2][128];
	for (int i = 0; i < Q; i++) {
		int mn = 0;
		for (int j = 0; j < clNeedDevCnt; j++) {
			if (workload[j] < workload[mn])
				mn = j;
		}
		assignGPU(procBuff[i], mn);
		workload[mn] += procBuff[i]->h;
		workQue[mn][workQueSz[mn]++] = procBuff[i];
	}
	executeGPU(workQue, workQueSz, resultBuff, clCallFunc);
	for (int i = 0; i < Q; i++)
		printf("%u\n", resultBuff[i]);
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
	if (signal(SIGKILL, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);
	if (signal(SIGINT, sigHandler) == SIG_ERR)     
		fprintf(stderr, sigErr);

	onStart(clCallFuncOuter);
	return 0;
}
