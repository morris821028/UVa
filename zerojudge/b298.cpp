#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[32767];
int wa[32767];
int dfs(int u) {
	wa[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!wa[v])	dfs(v);
	}
}
int main() {
	int n, m, l, q;
	int x, y;
	while (scanf("%d %d %d %d", &n, &m, &l, &q) == 4) {
		for (int i = 0; i <= n; i++)
			g[i].clear(), wa[i] = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
		}
		for (int i = 0; i < l; i++) {
			scanf("%d", &x);
			dfs(x);
		}
		for (int i = 0; i < q; i++) {
			scanf("%d", &x);
			puts(!wa[x] ? "YA~~" : "TUIHUOOOOOO");
		}
	}
	return 0;
}
