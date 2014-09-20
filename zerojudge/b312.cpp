#include <stdio.h>
#include <string.h> 
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 5005
struct edge {
	int to, v;
	edge(int a = 0, int b = 0):
		to(a), v(b) {}
};
vector<edge> g[MAXN];
int dist[MAXN], inq[MAXN];
int spfa(int s, int e) {
	memset(dist, 63, sizeof(dist));
	memset(inq, 0, sizeof(inq));
	queue<int> Q;
	int u, v, w;
	dist[s] = 0, Q.push(s);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].to, w = g[u][i].v;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					Q.push(v);
				}
			}
		}
	}
	return dist[e];
}
int main() {
	int n, m, s, e;
	int x, y, w;
	while (scanf("%d %d %d %d", &n, &m, &s, &e) == 4) {
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(edge(y, w));
			g[y].push_back(edge(x, w));
		}
		printf("%d\n", spfa(s, e));
	}
	return 0;
}
