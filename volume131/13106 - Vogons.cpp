#include <bits/stdc++.h>
using namespace std;
const int MAXN = 512;
int g[MAXN][MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				scanf("%d", &g[i][j]);
		}
		
		int gc[MAXN] = {};
		for (int i = 1; i <= m; i++) {
			int dp[MAXN] = {};
			for (int j = 1; j <= n; j++)
				dp[j] = max(dp[j-1], (j-2 >= 0 ? dp[j-2] : 0) + g[j][i]);
			for (int j = 1; j <= n; j++)
				gc[i] = max(gc[i], dp[j]);
		}
		
		int dp[MAXN] = {}, ret = 0;
		for (int i = 1; i <= m; i++) {
			dp[i] = max(dp[i-1], (i-2 >= 0 ? dp[i-2] : 0) + gc[i]);
			ret = max(ret, dp[i]);
		}
		printf("%d\n", ret);
	}
	return 0;
}

