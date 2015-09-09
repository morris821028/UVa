#include <bits/stdc++.h>
using namespace std;
const int MAXN = 32767;
vector<int> g[MAXN], invg[MAXN];
int test[MAXN], dist[MAXN], ban[MAXN];
void ban_bfs(int st) {
	queue<int> Q;
	int u, v;
	Q.push(st), test[st] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		for (auto v : invg[u]) {
			if (test[v] == 0)
				test[v] = 1, Q.push(v);
		}
	}
}
void bfs(int st) {
	queue<int> Q;
	int u, v;
	Q.push(st), dist[st] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		for (auto v : g[u]) {
			if (ban[v])
				continue;
			if (dist[v] == 0)
				dist[v] = dist[u]+1, Q.push(v);
		}
	}
}
int main() {
	int n, m, x, y, st, ed;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			g[i].clear(), ban[i] = 1, dist[i] = 0, test[i] = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			invg[y].push_back(x);
		}
		scanf("%d %d", &st, &ed);
		ban_bfs(ed);
		for (int i = 1; i <= n; i++) {
			int ok = 1;
			for (auto v : g[i])
				ok &= test[v];
			ban[i] = !ok;
		}
		bfs(st);
		printf("%d\n", dist[ed] - 1);
	}
	return 0;
}

