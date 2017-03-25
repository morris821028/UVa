#include <stdio.h>
#include <string.h>

int main() {
	int n, m;
#define MAXN 1024
#define MAXM 512
	while (scanf("%d%d", &n, &m) == 2) {
		static int A[MAXN], W[MAXN][MAXN];
		static int dp[MAXM][MAXN];
		static int arg[MAXN][MAXN];
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
			
		for (int i = 1; i <= n; i++) {
			int lsum = 0, rsum = 0;
			int p = i, cos = 0;
			W[i][i] = 0;
			for (int j = i-1; j >= 1; j--) {
				while (p > j && lsum - rsum + A[p] - A[j] <= 0) {
					cos += lsum - rsum + A[p];
					lsum += A[p], rsum -= A[p-1];
					p--;
				}
				cos += A[j] * (p-j);
				rsum += A[j], W[i][j] = cos;
			}
		}
		
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[1][i] = W[i][1], arg[1][i] = 0;
		for (int i = 2; i <= m; i++) {
			arg[i][n+1] = n;
			for (int j = n; j >= i; j--) {
				int ret = dp[i][j], arg_t = -1;
				int l = arg[i-1][j], r = arg[i][j+1];
				for (int k = l; k <= r; k++) {
					int c = W[j][k+1];
					if (dp[i-1][k]+c < ret) 
						ret = dp[i-1][k]+c, arg_t = k;
				}
				dp[i][j] = ret, arg[i][j] = arg_t;
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
