#include <bits/stdc++.h>
using namespace std;
const int MAXV = 1024;
vector<int> g[MAXV];
int visited[MAXV];
int dfs(int u) {
	visited[u] = 1;
	for (auto &v : g[u]) {
		if (visited[v] == 1)
			return 1;
		if (visited[v] == 0 && dfs(v))
			return 1;
	} 
	visited[u] = 2;
	return 0;
}
int main() {
	int testcase, n, m, x, y, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			g[i].clear(), visited[i] = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
		}
		int ret = 0;
		for (int i = 1; i <= n && !ret; i++)
			if (visited[i] == 0)
				ret |= dfs(i);
		puts(ret ? "O______O" : "W+W");
	}
	return 0;
}

