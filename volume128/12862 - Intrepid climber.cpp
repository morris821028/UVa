#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
vector< pair<int, int> > g[131072];
int f[131072], w = 0, ret = 0;
void dfs(int u, int &friends, int dep) {
	int v, ff = 0, cost;
	friends = f[u];
	if (f[u])	ret = max(ret, dep);
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i].first;
		dfs(v, ff, dep + g[u][i].second);
		if (ff > 0) {
			w += g[u][i].second;
			friends += ff;
		}
	}
}
int main() {
	int n, m, x, y, v;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			g[i].clear(), f[i] = 0;
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &x, &y, &v);
			g[x].push_back(make_pair(y, v));
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			f[x] = 1;
		}
		w = 0, ret = 0;
		dfs(1, x, 0);
		printf("%d\n", w - ret);
	}
	return 0;
}
/*
6 2
1 2 2
2 4 2
1 3 3
3 6 3
3 5 1
5 2
4 2
1 2 2
1 3 1
3 4 2
2 4
4 2
1 4 1
1 3 1
4 2 2
2 4
*/
