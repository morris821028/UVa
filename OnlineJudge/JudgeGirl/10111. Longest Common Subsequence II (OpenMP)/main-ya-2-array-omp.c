#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define MAXN 60005
#define CHARSET 4
#define DP_TYPE unsigned short
int lcs_len_seq(const char *A, int na, const char *B, int nb, int dpf[]) {
	static DP_TYPE dp[2][MAXN];
	memset(dp[0], 0, sizeof(DP_TYPE)*(nb+1));
    dp[1][0] = 0;
#define max(x, y) (x) > (y) ? (x) : (y)
    for (int i = 1; i <= na; i++) {
        for (int j = 1; j <= nb; j++) {
            if (A[i-1] == B[j-1])
                dp[1][j] = dp[0][j-1]+1;
            else
                dp[1][j] = max(dp[1][j-1], dp[0][j]);
        }
        memcpy(dp[0], dp[1], sizeof(DP_TYPE)*(nb+1));
    }
#undef max
    for (int i = 0; i <= nb; i++)
        dpf[i] = dp[0][i];
    return dpf[nb];
}
int lcs_len(const char *A, int na, const char *B, int nb, int dpf[]) {
	if (nb < 500)
		return lcs_len_seq(A, na, B, nb, dpf);
    static int c2i[128] = {['A'] = 0, ['C'] = 1, ['G'] = 2, ['T'] = 3};
    static char i2c[CHARSET] = {'A', 'C', 'G', 'T'};
    static int P[CHARSET][MAXN];
    static DP_TYPE dp[2][MAXN];
    A--, B--;
    #pragma omp parallel for
    for (int i = 0; i < CHARSET; i++) {
        memset(P[i], 0, sizeof(int)*(nb+1));
        for (int j = 1; j <= nb; j++)
            P[i][j] = (B[j] == i2c[i])? j : P[i][j-1];
    }
    for (int i = 0; i < 2; i++)
        memset(dp[i], 0, sizeof(DP_TYPE)*(nb+1));
#define max(x, y) (x) > (y) ? (x) : (y)
#pragma omp parallel
    for (int i = 1; i <= na; i++) {
        int v = c2i[A[i]];
        #pragma omp for
        for (int j = 1; j <= nb; j++) {
            int last_match = P[v][j];
            DP_TYPE tmp = last_match ? dp[i&1^1][last_match-1]+1 : 0;
            dp[i&1][j] = max(dp[i&1^1][j], tmp);
        }
    }
#undef max
    for (int i = 0; i <= nb; i++)
        dpf[i] = dp[na&1][i];
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

	static int t1[MAXN];
	static int t2[MAXN];
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
	static char A[MAXN], B[MAXN];
	int dp[MAXN];
	while (scanf("%s %s", A, B) == 2) {
		int na = strlen(A);
		int nb = strlen(B);
		int len = lcs_len(A, na, B, nb, dp);
		char *str = find_lcs(A, na, B, nb);
		printf("%d\n", len);
		printf("%s\n", str);
		free(str);
	}
	return 0;
}


