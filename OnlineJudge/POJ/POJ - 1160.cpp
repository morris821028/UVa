#include <stdio.h>
#include <string.h>

int cost(int l, int r, int p, int S[], int A[]) {
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
		int dp[32][512];
		memset(dp, 0x3f, sizeof(dp));
		const int INF = dp[0][0];
		dp[0][0] = 0;
		for (int i = 0; i <= n; i++) {
			for (int k = 0; k < m; k++) {
				int p = i+1;
				if (dp[k][i] == INF)
					continue;
				for (int j = i+1; j <= n; j++) {
					int c = cost(i+1, j, (i+1+j)/2, S, A);
					dp[k+1][j] = min(dp[k+1][j], dp[k][i]+c);
				}
			}
		}
		printf("%d\n", dp[m][n]);
	}
	return 0;
}

