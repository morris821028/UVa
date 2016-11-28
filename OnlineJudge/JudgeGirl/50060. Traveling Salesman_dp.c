#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int g[16][16];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &g[i][j]);
		int dp[1<<n][n];
		memset(dp, 0x3f, sizeof(dp));
		int INF = dp[0][0];
		dp[0][0] = 0;
		for (int i = 0; i < (1<<n); i++) {
			for (int j = 0; j < n; j++) {
				if (dp[i][j] == INF)
					continue;
				int c = dp[i][j];
				for (int k = 0; k < n; k++) {
					if ((i>>k)&1)
						continue;
					if (c + g[j][k] < dp[i|(1<<k)][k])
						dp[i|(1<<k)][k] = c + g[j][k];
				}
			}
		}
		printf("%d\n", dp[(1<<n)-1][0]);
	}
	return 0;
}



