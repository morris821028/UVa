#include <stdio.h> 
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
struct edge {
	int to;
	long long a, b, t;
	edge(int x = 0, int y = 0, int z = 0, int w = 0):
		to(x), a(y), b(z), t(w) {}
};
vector<edge> g[512];
long long dist[512], inq[512];
long long spfa(int st, int ed, int n) {
	memset(dist, 0x3f, sizeof(dist));
	memset(inq, 0, sizeof(inq));
	queue<int> Q;
	int u, v;
	long long a, b, t;
	Q.push(st), dist[st] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].to;
			a = g[u][i].a, b = g[u][i].b, t = g[u][i].t;
			if (a < t)	continue; // important
			long long cost = 0;
			if (dist[u]%(a + b) + t <= a)
				cost = dist[u] + t;
			else 
				cost = dist[u] + a + b - dist[u]%(a + b) + t;
			if (cost < dist[v]) {
				dist[v] = cost;
				if (!inq[v])
					inq[v] = 1, Q.push(v);
			}
		}
	}
	return dist[ed];
}
int main() {
	int n, m, st, ed, cases = 0;
	int x, y, a, b, t;
	while (scanf("%d %d %d %d", &n, &m, &st, &ed) == 4) {
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d %d", &x, &y, &a, &b, &t);
			g[x].push_back(edge(y, a, b, t));
		}
		
		long long ret = spfa(st, ed, n);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
3 2 1 3
1 2 5 6 3
2 3 7 7 6
3 2 1 3
1 2 5 6 3
2 3 9 5 6
*/
