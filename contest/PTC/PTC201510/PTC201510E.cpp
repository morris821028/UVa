#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
vector<int> g[MAXN];
void dfs(int u, int p, int ret[]) {
	// 0: no place, 1: place and no colleague, 2: place and colleague
	ret[0] = 0, ret[1] = 1, ret[2] = 1;
	int sum = 0, mnv = MAXN;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v == p)	continue;
		int tmp[3];
		dfs(v, u, tmp);
		ret[0] += tmp[2];
		ret[1] += min(min(tmp[0], tmp[1]), tmp[2]);
		sum += min(min(tmp[0], tmp[1]), tmp[2]);
		mnv = min(mnv, min(tmp[1], tmp[2]) - tmp[0]);
	}
	mnv = max(0, mnv);
	ret[2] += sum + mnv;
}
int main() {
	int testcase;
	int n, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}
		int dp[3];
		dfs(1, -1, dp);
		printf("%d\n", min(dp[0], dp[2]));
	}
	return 0;
}
