#include <stdio.h> 
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
// each chamber is part of at most one cycle.
vector< pair<int, int> > g[10005];
int visited[10005], dist[10005], cycle[10005];
int dfs(int u, int p, int st, int cost) {
	visited[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first, w = g[u][i].second;
		if (v == st && v != p)	
			return cost + w;
		if (visited[v] == 0) {
			int ret = dfs(v, u, st, cost + w);
			if (ret) {
				cycle[u] = cycle[v] = ret;
				return ret;
			}
		}
	}
	return 0;
}
void dijkstra(int st, int n) {
	for (int i = 1; i <= n; i++)
		dist[i] = 1e+9;
	int u, v, d;
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > Q;
	Q.push(make_pair(0, st)), dist[st] = 0;
	
	while (!Q.empty()) {
		u = Q.top().second, d = Q.top().first;
		Q.pop();
		if (dist[u] < d)	continue;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first, w = g[u][i].second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				Q.push(make_pair(dist[v], v));
			}
		}
	}
}
int main() {
	int n, m, q, st;
	int x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			g[i].clear(), cycle[i] = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(make_pair(y, w));
			g[y].push_back(make_pair(x, w));
		}
		for (int i = 1; i <= n; i++) {
			if (cycle[i] == 0 && g[i].size() > 1) {
				memset(visited, 0, sizeof(visited));
				cycle[i] = dfs(i, i, i, 0);
			}
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%d %d", &st, &w);
			dijkstra(st, n);
			int ret = 1e+9;
			for (int i = 1; i <= n; i++) {
				if (cycle[i] >= w)
					ret = min(ret, cycle[i] + dist[i] * 2);
			}
			printf("%d\n", ret == 1e+9 ? -1 : ret);
		}
	}
	return 0;
}
/*
4 4
1 2 12
2 3 10
3 4 8
2 4 5
3
1 23
4 10
1 24
8 9
1 2 1
2 3 1
3 4 1
2 5 10
5 6 25
2 6 20
3 7 9
7 8 3
3 8 4
4
1 10
4 60
8 5
7 55
*/
