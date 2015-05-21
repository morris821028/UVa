#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 8192;
int n, m, st, ed, h[MAXN];
vector< pair<int, int> > g[MAXN];

int dist[MAXN], inq[MAXN];
void spfa(int st, int ed, int n) {
	for (int i = 0; i < n; i++)
		dist[i] = 0x3f3f3f3f, inq[i] = 0;
	queue<int> Q;
	int u, v, w;
	dist[ed] = 0, Q.push(ed);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++)  {
			v = g[u][i].first, w = g[u][i].second;
			if (h[v] > h[u]) {
				if (dist[v] > max(dist[u] - (h[v] - h[u]) + w, 0)) {
					dist[v] = max(dist[u] - (h[v] - h[u]) + w, 0);
					if (inq[v] == 0) {
						inq[v] = 1;
						Q.push(v);
					}
				}
			} else {
				if (dist[v] > dist[u] + (h[u] - h[v]) + w) {
					dist[v] = dist[u] + (h[u] - h[v]) + w;
					if (inq[v] == 0) {
						inq[v] = 1;
						Q.push(v);
					}
				} 
			}
			
		}
	}
	printf("%d\n", dist[st]);
}
int main() {
	int testcase;
	int u, v, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &n, &m, &st, &ed);
		st--, ed--;
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < n; i++)
			scanf("%d", &h[i]);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			g[u].push_back(make_pair(v, w));
			g[v].push_back(make_pair(u, w));
		}
		
		spfa(st, ed, n);
	}
	return 0;
}
