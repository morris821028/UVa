#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
int D, T, N, M;
int fee[16], fun[16], g[16][16];

int used[1<<16][16], dp[1<<16][16];
int dfs(int mask, int last, int time, int cost) {
	if (time + g[last][0] > T)
		return -0x3f3f3f3f;
	if (used[mask][last])
		return dp[mask][last];
	used[mask][last] = 1;
	int &ret = dp[mask][last];
	ret = 0;
	for (int i = 0; i < N; i++) {
		if (i == last)	continue;
		if ((mask>>i)&1) {
			if (cost + fee[i] <= D) {
				ret = max(ret, fun[i] + dfs(mask^(1<<i), i, time + 15 + g[last][i], cost + fee[i]));
			}
		}
	}
	return ret;
}
int main() {
	int testcase, cases = 0, x, y, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &D, &T, &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d %d", &fee[i], &fun[i]);
		N++;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				g[i][j] = 0x3f3f3f3f;
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x][y] = g[y][x] = min(g[x][y], w);
		}
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
		memset(used, 0, sizeof(used));
		int ret = dfs((1<<N)-1, 0, 0, 0);
		printf("Case %d: ", ++cases);
		if (ret > 0)
			printf("%d\n", ret);
		else
			puts("No possible trip.");
	}
	return 0;
}
