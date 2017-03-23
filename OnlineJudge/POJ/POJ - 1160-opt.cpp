#include <stdio.h>
#include <string.h>

int w(int l, int r, int S[], int A[]) {
	int p = (l+r)/2;
	int lsum = S[p] - S[l-1];
	int rsum = S[r] - S[p];
	return (A[p]*(p-l+1) - lsum) + (rsum - A[p]*(r-p));
}
int min(int x, int y) {
	return x < y ? x : y;
}
int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		int A[512], S[512] = {};
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
			S[i] = S[i-1] + A[i];
		}
		static int dp[32][512];
		memset(dp, 0x3f, sizeof(dp));
		
		int arg[512][512];
		for (int i = 1; i <= n; i++)
			dp[1][i] = w(1, i, S, A), arg[1][i] = 0;
		for (int i = 2; i <= m; i++) {
			arg[i][n+1] = n;
			for (int j = n; j >= i; j--) {
				for (int k = arg[i-1][j]; k <= arg[i][j+1]; k++) {
					int c = w(k+1, j, S, A);
					if (dp[i-1][k] + c < dp[i][j]) {
						dp[i][j] = dp[i-1][k] + c;
						arg[i][j] = k;
					}
				}
			}
		}
		printf("%d\n", dp[m][n]);
	}
	return 0;
}

