#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 1024;
vector<int> g[MAXN];
int visited[MAXN];

int dfs(int u, int &p, int &q) {
	for (auto v : g[u]) {
		if (visited[v] == 0) {
			visited[v] = 3-visited[u];
			p += visited[v] == 1;
			q += visited[v] == 2;
			if (dfs(v, p, q))
				return 1;
		} else {
			if (visited[v] == visited[u])
				return 1;
		}
	}
	return 0;
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i <= n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		memset(visited, 0, sizeof(visited));
		int valid = 1, ret = 0;
		for (int i = 1; i <= n && valid; i++) {
			if (visited[i])
				continue;
			int p = 0, q = 0;
			visited[i] = 1, p++;
			int t = dfs(i, p, q);
//			printf("-- %d %d %d\n", i, p, q);
			if (t == 1)
				valid = 0;
			ret += min(p, q);
		}
		if (valid)
			printf("%d\n", ret);
		else
			puts("Impossible");
	}
	return 0;
}
/*
7  4
1  2
1  3
4  5
6  5

5  6
1  2
1  3
2  4
3  4
3  5
4  5

*/
