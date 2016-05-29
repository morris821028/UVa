#include <cstdio>
#include <cstdlib>
#define MAXN 60005
#define CHARSET 4
typedef unsigned short uint16;
static char A[MAXN], B[MAXN];
static int c2i[128];
static char i2c[CHARSET+1] = "ACGT";
static int *cuP;
static char *cuB;
static uint16 *cuDP;
__global__ void prepare(int *P, char *B, int nb) {
	int i = threadIdx.x;
	int *p = P + i*MAXN;
	char c = "ACGT"[i];
	p[0] = 0;
	for (int j = 1; j <= nb; j++)
		p[j] = (B[j] == c) ? j : p[j-1];
}
__global__ void run(int nb, uint16 *dpIn, uint16 *dpOut, int *P) {
	int j = blockDim.x*blockIdx.x+threadIdx.x+1;
	if (j > nb)	return ;
	int pos = P[j];
	uint16 t1 = pos ? dpIn[pos-1]+1 : 0;
	uint16 t2 = dpIn[j];
	dpOut[j] = t1 > t2 ? t1 : t2;
}
int lcs_len(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	B--;
	cudaMemcpy(cuB, B, sizeof(char)*(nb+1), cudaMemcpyHostToDevice);
	cudaMemset(cuDP, 0, sizeof(uint16)*(nb+1));
	cudaMemset(cuDP+MAXN, 0, sizeof(uint16)*(nb+1));
	
	int bsz = 1024;
	dim3 bb(bsz);
	dim3 gg((nb+bsz-1)/bsz);
	prepare<<<1, 4>>>(cuP, cuB, nb);
	for (int i = 0; i < na; i++) {
		int v = c2i[A[i]];
		run<<<gg, bb>>>(nb, cuDP+(i&1)*MAXN, cuDP+((i&1)^1)*MAXN, cuP+v*MAXN);
	}
	cudaMemcpy(dpf, cuDP+(na&1)*MAXN, sizeof(uint16)*(nb+1), cudaMemcpyDeviceToHost);
	return dpf[nb];
}
int main() {
	for (int i = 0; i < CHARSET; i++)
		c2i[i2c[i]] = i;
	cudaMalloc(&cuB, sizeof(char)*MAXN);
	cudaMalloc(&cuP, sizeof(int)*MAXN*4);
	cudaMalloc(&cuDP, sizeof(uint16)*MAXN*2);
	static uint16 dpf[MAXN];
    while (scanf("%s %s", A, B) == 2) {
        int len = lcs_len(A, strlen(A), B, strlen(B), dpf);
        printf("%d\n", len);
    }
	cudaFree(cuB);
	cudaFree(cuP);
	cudaFree(cuDP);
    return 0;
}


