#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#define MAXN 60005
#define MAXSEQ 500
#define CHARSET 4
#define max(x, y) (x) > (y) ? (x) : (y)
static __thread int c2i[128] = {['A'] = 0, ['C'] = 1, ['G'] = 2, ['T'] = 3};
int lcs_len(const char *A, int na, const char *B, int nb, int inv_flag, int dpf[]) {
    static int P[CHARSET][MAXN];
    int dp[2][MAXN] = {};
	A--, B--;
	if (!inv_flag) {
#pragma omp parallel for
		for (int i = 0; i < CHARSET; i++) {
			P[i][0] = nb+1;
			for (int j = 1; j <= nb; j++)
				P[i][j] = (B[j] == "ACGT"[i]) ? j-1 : P[i][j-1];
		}
		for (int i = 0; i < 2; i++)
			dp[i][nb+1] = -1;
#pragma omp parallel
		for (int i = 1; i <= na; i++) {
			int *Pv = P[c2i[A[i]]];
			int *dpIn = dp[i&1^1];
			int *dpOut = dp[i&1];
#pragma omp for
			for (int j = 1; j <= nb; j++) {
				int t1 = dpIn[Pv[j]]+1;
				int t2 = dpIn[j];
				dpOut[j] = t1 > t2 ? t1 : t2;
			}
		}
		memcpy(dpf, dp[na&1], sizeof(int)*(nb+1));
		dpf[nb+1] = dpf[0] = 0;
		return dpf[nb];
	}
	// inverse version	
#pragma omp parallel for
	for (int i = 0; i < CHARSET; i++) {
		P[i][nb+1] = 0;
		for (int j = nb; j >= 1; j--)
			P[i][j] = (B[j] == "ACGT"[i]) ? j+1 : P[i][j+1];
	}
	for (int i = 0; i < 2; i++)
		dp[i][0] = -1;
#pragma omp parallel
	for (int i = na; i >= 1; i--) {
		int *Pv = P[c2i[A[i]]];
		int *dpIn = dp[i&1^1];
		int *dpOut = dp[i&1];
#pragma omp for
		for (int j = 1; j <= nb; j++) {
			int t1 = dpIn[Pv[j]]+1;
			int t2 = dpIn[j];
			dpOut[j] = t1 > t2 ? t1 : t2;
		}
	}
	memcpy(dpf, dp[1&1], sizeof(int)*(nb+1));
	dpf[nb+1] = dpf[0] = 0;
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
char* find_lcs_seq(const char *A, int na, const char *B, int nb) {
	static int P[CHARSET][MAXSEQ];
	static char fa[MAXSEQ][MAXSEQ];
	int dp[2][MAXSEQ] = {};
	A--, B--;
	for (int i = 0; i < CHARSET; i++) {
		P[i][0] = nb+1;
		for (int j = 1; j <= nb; j++)
			P[i][j] = (B[j] == "ACGT"[i]) ? j-1 : P[i][j-1];
	}
	for (int i = 0; i < 2; i++)
		dp[i][nb+1] = -1;
	for (int i = 1; i <= na; i++) {
		int *Pv = P[c2i[A[i]]];
		int *dpIn = dp[i&1^1];
		int *dpOut = dp[i&1];
		for (int j = 1; j <= nb; j++) {
			int t1 = dpIn[Pv[j]]+1;
			int t2 = dpIn[j];
			if (t1 > t2)
				dpOut[j] = t1, fa[i][j] = 0;
			else
				dpOut[j] = t2, fa[i][j] = 1;
		}
	}
	int sz = dp[na&1][nb];
	char *ret = alloc_str(sz+1);
	for (int i = na, j = nb; sz && i >= 1; i--) {
		if (fa[i][j] == 0)
			ret[--sz] = A[i], j = P[c2i[A[i]]][j];
	}
	return ret;
}
char* find_lcs(const char *a, int na, const char *b, int nb) {
	if (na > nb) {
		const char *c; int t;
		c = a, a = b, b = c;
		t = na, na = nb, nb = t;
	}

	if (na == 0)
		return alloc_str(1);
	if (na < MAXSEQ && nb < MAXSEQ)
		return find_lcs_seq(a, na, b, nb);

	int t1[MAXN];
	int t2[MAXN];
	int len = -1;
	int half_len = na / 2;
	char *la = substr(a, 0, half_len);
	char *ra = substr(a, half_len, na - half_len);
	lcs_len(la, half_len, b, nb, 0, t1);
	lcs_len(ra, na - half_len, b, nb, 1, t2);

	int split = -1;
	for (int i = 0; i <= nb; i++) {
		if (t1[i] + t2[i+1] > len)
			split = i, len = t1[i] + t2[i+1];
	}
	if (len == 0) 
		return alloc_str(1);
	assert(split != -1);
	char *lb = substr(b, 0, split);
	char *rb = substr(b, split, nb - split);
	char *sl = t1[split] ? find_lcs(la, half_len, lb, split) : alloc_str(1);
	char *sr = t2[split+1] ? find_lcs(ra, na - half_len, rb, nb - split) : alloc_str(1);
	char *ret = cat(sl, sr);
	free(la), free(ra);
	free(lb), free(rb);
	free(sl), free(sr);
	return ret;
}
int main() {
	static char A[MAXN], B[MAXN];
	int dp[MAXN];
	while (scanf("%s %s", A, B) == 2) {
		int na = strlen(A);
		int nb = strlen(B);
		char *str = find_lcs(A, na, B, nb);
		printf("%d\n", strlen(str));
		printf("%s\n", str);
		free(str);
	}
	return 0;
}


