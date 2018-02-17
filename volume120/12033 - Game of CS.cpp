#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024;
vector<pair<int, int>> g[MAXN];
int dfs(int u, int p) {
	int ret = 0;
	// 0: lose, 1: win
	for (auto e : g[u]) {
		if (e.first == p)
			continue;
		int sg = dfs(e.first, u);
		int w = e.second;
		if (w == 1)
			sg = sg+1;	// special case
		else if (w&1)
			sg = sg^1;
		ret ^= sg;
	}
	return ret;
}
int main() {
	int testcase, n, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back({y, w});
			g[y].push_back({x, w});
		}
		int ret = dfs(0, -1);
		printf("Case %d: %s\n", ++cases, ret ? "Emily" : "Jolly");
	}
	return 0;
}
/*
4
4
0 1 1
1 2 1
0 3 2
5
0 1 1
1 2 2
0 3 3
0 4 7
3
0 1 1
0 2 1
4
0 1 1
1 2 1
1 3 1
*/
