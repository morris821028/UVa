#include <stdio.h>
#include <string.h>
#include <omp.h>
#define MAXN 60005
#define CHARSET 4
#define DP_TYPE unsigned short
static char A[MAXN], B[MAXN];
int lcs_len(const char *A, int na, const char *B, int nb, int dpf[]) {
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
		int *Pv = P[c2i[A[i]]];
    	#pragma omp for
		for (int j = 1; j <= nb; j++) {
			int last_match = Pv[j];
			DP_TYPE tmp = last_match ? dp[i&1^1][last_match-1]+1 : 0;
			dp[i&1][j] = max(dp[i&1^1][j], tmp);
		}
	}
#undef max
	for (int i = 0; i <= nb; i++) 
		dpf[i] = dp[na&1][i];
    return dpf[nb];
}
int main() {
    int dp[MAXN];
    while (scanf("%s %s", A, B) == 2) {
        int len = lcs_len(A, strlen(A), B, strlen(B), dp);
        printf("%d\n", len);
    }
    return 0;
}
