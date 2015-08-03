#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int main() {
	int n, m, a[MAXN];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		int dp[MAXN][MAXN] = {};
		dp[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				for (int k = 0; k <= a[i] && j-k >= 0; k++) {
					dp[i][j] += dp[i-1][j-k];
					if (dp[i][j] >= 1000007)
						dp[i][j] -= 1000007;
				}
			}
		}
		printf("%d\n", dp[n][m]);
	}
	return 0;
}
