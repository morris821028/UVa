#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int profit[16], dp[1<<16];
int g[16], used[1<<16];
int dfs(int s, int n) {
	if (used[s])	return dp[s];
	if (s == 0)		return 0;
	used[s] = 1;
	int &ret = dp[s];
	int vs = (1<<n)-1 - s;
	ret = -0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		if (s == (1<<n)-1 || ((g[i]&vs) && ((s>>i)&1))) {
			ret = max(ret, profit[i] - dfs(s^(1<<i), n));
		}
	}
	return ret;
}
int main() {
	int n, m, x, y;
	while (scanf("%d", &n) == 1 && n) {
		int sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &profit[i]);
			g[i] = 0, sum += profit[i];
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			g[x] |= 1<<y, g[y] |= 1<<x;
		}
		
		memset(used, 0, sizeof(used));
		int mxDiff = dfs((1<<n)-1, n);
		if (mxDiff == 0) {
			printf("Tie game! %d all.\n", sum/2);
		} else if (mxDiff > 0) {
			printf("First player wins! %d to %d.\n", (sum + mxDiff)/2, (sum - mxDiff)/2);
		} else {
			printf("Second player wins! %d to %d.\n", (sum - mxDiff)/2, (sum + mxDiff)/2);
		}
	}
	return 0;
}
