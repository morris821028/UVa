#include <bits/stdc++.h> 
using namespace std;
const int MAXV = 500005;
const int MAXE = 500005;
const long long INF = 1LL<<60;
struct Edge {
	int to, eid;
	long long w;
	Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
long long dist[MAXV];
void addEdge(int x, int y, long long v)  {
	edge[e].to = y, edge[e].w = v, edge[e].eid = e;
	edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, long long dist[], int n, int ed = INT_MAX) {
typedef pair<long long, int> PLL;
	for (int i = 0; i <= n; i++)
		dist[i] = INF;
	set<PLL> pQ;
	PLL u;
	pQ.insert(PLL(0, st)), dist[st] = 0;
	while (!pQ.empty()) {
		u = *pQ.begin(), pQ.erase(pQ.begin());
		for (Edge *p = adj[u.second]; p; p = p->next) {
			if (dist[p->to] > dist[u.second] + p->w) {
				if (dist[p->to] != INF)
					pQ.erase(pQ.find(PLL(dist[p->to], p->to)));
				dist[p->to] = dist[u.second] + p->w;
				pQ.insert(PLL(dist[p->to], p->to));
			}
		}
		if (u.second == ed)
			return ;
	}
}

int main() {
	int n, m;
	int x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		e = 0;
		for (int i = 1; i <= n; i++)
			adj[i] = NULL;
		
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			addEdge(x, y, w);
		}
		
		dijkstra(1, dist, n, n);
		printf("%lld\n", dist[n]);
	}
	return 0;
}
