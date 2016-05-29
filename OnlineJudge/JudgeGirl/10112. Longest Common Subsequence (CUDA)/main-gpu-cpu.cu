#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <omp.h>
#include <device_functions_decls.h>
using namespace std;
#define CheckErr(status) { gpuAssert((status), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, int abort=true) {
    if (code != cudaSuccess) {
        fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if (abort) exit(code);
    }
}
#define MAXN 60005
#define CHARSET 4
typedef unsigned short uint16;
static char A[MAXN], B[MAXN];
static int c2i[128] = {};
static char i2c[CHARSET] = {'A', 'C', 'G', 'T'};
static uint16 *cuDP;
static int *cuP;
static char *cuA, *cuB;
__device__ inline int char2int(char c) {
	switch(c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
	}
	return 0;
}
__global__ void run(char *A, int na, char *B, int nb, int i, uint16 *dp, int *P) {
	int j = blockDim.x*blockIdx.x+threadIdx.x+1;
	if (j > nb)	return ;
	int v = char2int(A[i]); 
	int last_match = P[v*MAXN+j];
	uint16 t1 = last_match ? dp[((i&1)^1)*MAXN + last_match-1]+1 : 0;
	uint16 t2 = dp[((i&1)^1)*MAXN + j];
	dp[(i&1)*MAXN + j] = t1 > t2 ? t1 : t2;
}
int lcs_len(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	static int P[CHARSET][MAXN];
    static uint16 dp[2][MAXN];
	A--, B--;
    #pragma omp parallel for
    for (int i = 0; i < CHARSET; i++) {
        memset(P[i], 0, sizeof(int)*(nb+1));
        for (int j = 1; j <= nb; j++)
            P[i][j] = (B[j] == i2c[i])? j : P[i][j-1];
		cudaMemcpy(cuP+i*MAXN, P[i], sizeof(int)*(nb+1), cudaMemcpyHostToDevice);
    }
    for (int i = 0; i < 2; i++) {
        memset(dp[i], 0, sizeof(uint16)*(nb+1));
		cudaMemcpy(cuDP+i*MAXN, dp[i], sizeof(uint16)*(nb+1), cudaMemcpyHostToDevice);
	}
	cudaMemcpy(cuA, A, sizeof(char)*(na+1), cudaMemcpyHostToDevice);
	cudaMemcpy(cuB, B, sizeof(char)*(nb+1), cudaMemcpyHostToDevice);
	int bsz = 512;
	dim3 bb(bsz);
	dim3 gg((nb+bsz-1)/bsz);
	for (int i = 1; i <= na; i++)
		run<<<gg, bb>>>(cuA, na, cuB, nb, i, cuDP, cuP);
	cudaMemcpy(dpf, cuDP+(na&1)*MAXN, sizeof(uint16)*(nb+1), cudaMemcpyDeviceToHost);
	return dpf[nb];
}
int main() {
	for (int i = 0; i < CHARSET; i++)
		c2i[i2c[i]] = i;
	cudaMalloc(&cuA, sizeof(char)*MAXN);
	cudaMalloc(&cuB, sizeof(char)*MAXN);
	cudaMalloc(&cuP, sizeof(int)*MAXN*4);
	cudaMalloc(&cuDP, sizeof(uint16)*MAXN*2);
	static uint16 dpf[MAXN];
    while (scanf("%s %s", A, B) == 2) {
        int len = lcs_len(A, strlen(A), B, strlen(B), dpf);
        printf("%d\n", len);
    }
	cudaFree(cuA);
	cudaFree(cuB);
	cudaFree(cuP);
	cudaFree(cuDP);
    return 0;
}


