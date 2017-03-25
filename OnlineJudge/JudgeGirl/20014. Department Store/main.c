#include <stdio.h>
#include <string.h>

static inline int min(int x, int y) {
	return x < y ? x : y;
}
int main() {
	int n, m;
#define MAXN 1024
#define MAXM 512
	while (scanf("%d%d", &n, &m) == 2) {
		static int A[MAXN]; 
		static int dp[MAXM][MAXN], W[MAXN][MAXN];
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
		}
		for (int i = 1; i <= n; i++) {
			int lsum = 0, rsum = 0;
			int p = i, cos = 0;
			W[i][i] = 0;
			for (int j = i+1; j <= n; j++) {
				while (p < j && lsum - rsum + A[p] - A[j] <= 0) {
					cos += lsum - rsum + A[p];
					lsum += A[p], rsum -= A[p+1];
					p++;
				}
				cos += A[j] * (j-p), rsum += A[j];
				W[i][j] = cos;
			}
		}

		memset(dp, 0x3f, sizeof(dp));
		const int INF = dp[0][0];
		dp[0][0] = 0;
		for (int i = 0; i <= n; i++) {
			for (int k = 0; k < m; k++) {
				for (int j = i+1; j <= n; j++) {
					dp[k+1][j] = min(dp[k+1][j], dp[k][i]+W[i+1][j]);
				}
			}
		}
		printf("%d\n", dp[m][n]);
	}
	return 0;
}
/*
   10 5
   1 2 3 6 7 9 11 22 44 50

   12 2
   0 1 1 1 0 0 1 1 0 1 0 1
 */
