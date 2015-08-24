#include <bits/stdc++.h> 
using namespace std;
const int MAXV = 32767;
const int MAXE = 32767;
const long long INF = 1LL<<62;
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
void dijkstra(int st, long long dist[], int n) {
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
	}
}

int main() {
	int testcase, cases = 0, n, m;
	int x, y, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		
		e = 0;
		for (int i = 0; i <= n; i++)
			adj[i] = NULL;
			
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			addEdge(x, y, w);
			addEdge(y, x, w);
		}
		
		int on[65536] = {};
		for (int i = 0; i < n; i++) {
			dijkstra(i, dist, n);
			for (int j = 0; j < n; j++) {
				for (Edge *p = adj[j]; p; p = p->next) {
					if (dist[p->to] == dist[j] + p->w)
						on[p->eid/2] = 1;
				}
			}
		}
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < m; i++) {
			if (!on[i])
				printf("%d\n", i);
		}
	}
	return 0;
}
