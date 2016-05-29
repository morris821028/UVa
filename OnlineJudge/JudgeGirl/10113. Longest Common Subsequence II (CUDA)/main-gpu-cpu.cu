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
int lcs_len_seq(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
    static uint16 dp[2][MAXN];
    memset(dp[0], 0, sizeof(uint16)*(nb+1));
    dp[1][0] = 0;
#define max(x, y) (x) > (y) ? (x) : (y)
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (A[i-1] == B[j-1])
                dp[1][j] = dp[0][j-1]+1;
            else
                dp[1][j] = max(dp[1][j-1], dp[0][j]);
        }
        memcpy(dp[0], dp[1], sizeof(uint16)*(nb+1));
    }
#undef max
    for (int i = 0; i <= nb; i++)
        dpf[i] = dp[0][i];
    return dpf[nb];
}
int lcs_len(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	if (nb < 2048)
        return lcs_len_seq(A, na, B, nb, dpf);
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
char* alloc_str(int sz) {
    return (char *) calloc(sz, sizeof(char));
}
char* substr(const char *s, int pos, int len) {
    char *t = alloc_str(len+1);
    memcpy(t, s+pos, len);
    return t;
}
char* cat(const char *sa, const char *sb) {
    int na = strlen(sa), nb = strlen(sb);
    char *t = alloc_str(na + nb + 1);
    memcpy(t, sa, na);
    memcpy(t+na, sb, nb);
    return t;
}
char* reverse(const char *s, int len) {
    char *t = substr(s, 0, len);
    char *l = t, *r = t + len - 1;
    char tmp;
    while (l < r) {
        tmp = *l, *l = *r, *r = tmp;
        l++, r--;
    }
    return t;
}
char* find_lcs(const char *a, int na, const char *b, int nb) {
    if (na > nb) {
        const char *c; int t;
        c = a, a = b, b = c;
        t = na, na = nb, nb = t;
    }
 
    if (na == 0)
        return alloc_str(1);
 
    if (na == 1) {
        for (int i = 0; i < nb; i++) {
            if (a[0] == b[i])
                return substr(a, 0, 1);
        }
        return alloc_str(1);
    }
 
    static uint16 t1[MAXN];
    static uint16 t2[MAXN];
    int len = lcs_len(a, na, b, nb, t1);
    if (len == 0)
        return alloc_str(1);
    int half_len = na / 2;
    char *la = substr(a, 0, half_len);
    char *ra = substr(a, half_len, na - half_len);
    char *tb = reverse(b, nb);
    char *ta = reverse(ra, na - half_len);
    lcs_len(la, half_len, b, nb, t1);
    lcs_len(ta, na - half_len, tb, nb, t2);
 
    int split = -1;
    for (int i = 0; i <= nb; i++) {
        if (t1[i] + t2[nb-i] == len) {
            split = i;
            break;
        }
    }
 
    char *lb = substr(b, 0, split);
    char *rb = substr(b, split, nb - split);
    char *sl = find_lcs(la, half_len, lb, split);
    char *sr = find_lcs(ra, na - half_len, rb, nb - split);
    char *ret = cat(sl, sr);
    free(la), free(ra), free(ta);
    free(lb), free(rb), free(tb);
    free(sl), free(sr);
    return ret;
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
		int na = strlen(A);
        int nb = strlen(B);
        int len = lcs_len(A, na, B, nb, dpf);
		char *str = find_lcs(A, na, B, nb);
        printf("%d\n", len);
        printf("%s\n", str);
        free(str);	
    }
	cudaFree(cuA);
	cudaFree(cuB);
	cudaFree(cuP);
	cudaFree(cuDP);
    return 0;
}


