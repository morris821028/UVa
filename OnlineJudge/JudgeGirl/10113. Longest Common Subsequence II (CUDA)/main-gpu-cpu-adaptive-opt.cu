#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <omp.h>
using namespace std;
#define MAXN 60005
#define CHARSET 4
#define max(x, y) (x) > (y) ? (x) : (y)
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
    if (j > nb)    return ;
    int pos = P[j];
    uint16 t1 = pos ? dpIn[pos-1]+1 : 0;
    uint16 t2 = dpIn[j];
    dpOut[j] = t1 > t2 ? t1 : t2;
}
int lcs_len_seq(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	static uint16 dp[2][MAXN];
	memset(dp[0], 0, sizeof(uint16)*(nb+1));
	dp[1][0] = 0, dpf[0] = 0;
	for (int i = 1; i <= na; i++) {
		for (int j = 1; j <= nb; j++) {
			if (A[i-1] == B[j-1])
				dp[1][j] = dp[0][j-1]+1;
			else
				dp[1][j] = max(dp[1][j-1], dp[0][j]);
		}
		memcpy(dp[0], dp[1], sizeof(uint16)*(nb+1));
	}
	for (int i = 0; i <= nb; i++)
		dpf[i] = dp[0][i];
	return dpf[nb];
}
int lcs_len_omp(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	static int P[CHARSET][MAXN];
	static uint16 dp[2][MAXN];
	A--, B--;
#pragma omp parallel for
	for (int i = 0; i < CHARSET; i++) {
		memset(P[i], 0, sizeof(int)*(nb+1));
		for (int j = 1; j <= nb; j++)
			P[i][j] = (B[j] == i2c[i])? j : P[i][j-1];
	}
	for (int i = 0; i < 2; i++)
		memset(dp[i], 0, sizeof(uint16)*(nb+1));
#pragma omp parallel
	for (int i = 1; i <= na; i++) {
		int *Pv = P[c2i[A[i]]];
#pragma omp for
		for (int j = 1; j <= nb; j++) {
			int last_match = Pv[j];
			uint16 tmp = last_match ? dp[i&1^1][last_match-1]+1 : 0;
			dp[i&1][j] = max(dp[i&1^1][j], tmp);
		}
	}
	for (int i = 0; i <= nb; i++)
		dpf[i] = dp[na&1][i];
	return dpf[nb];
}
int lcs_len(const char *A, int na, const char *B, int nb, uint16 dpf[]) {
	if (max(na, nb) < 2048)
		return lcs_len_seq(A, na, B, nb, dpf);
	if (nb < 10000)
		return lcs_len_omp(A, na, B, nb, dpf);
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
	cudaFree(cuB);
	cudaFree(cuP);
	cudaFree(cuDP);
	return 0;
}


