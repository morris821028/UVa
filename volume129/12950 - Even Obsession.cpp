#include <bits/stdc++.h> 
using namespace std;
const int MAXV = 65536;
const int MAXE = 131072;
const long long INF = 1LL<<62;
struct Edge {
    int to, eid;
    long long w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
long long dist[MAXV][2];
void addEdge(int x, int y, long long v)  {
    edge[e].to = y, edge[e].w = v, edge[e].eid = e;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, long long dist[][2], int n) {
	struct PLL {
		long long d;
		int v, k;
		PLL(long long a = 0, int b = 0, int c = 0):
			d(a), v(b), k(c) {}
		bool operator<(const PLL &e) const {
			if (d != e.d)	return d < e.d;
			if (v != e.v)	return v < e.v;
			return k < e.k;
		}
	};
    for (int i = 0; i <= n; i++)
        dist[i][0] = dist[i][1] = INF;
    set<PLL> pQ;
    PLL u;
    pQ.insert(PLL(0, st, 0)), dist[st][0] = 0;
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        for (Edge *p = adj[u.v]; p; p = p->next) {
        	int tk = (u.k+1)%2;
            if (dist[p->to][tk] > dist[u.v][u.k] + p->w) {
                if (dist[p->to][tk] != INF)
                    pQ.erase(pQ.find(PLL(dist[p->to][tk], p->to, tk)));
                dist[p->to][tk] = dist[u.v][u.k] + p->w;
                pQ.insert(PLL(dist[p->to][tk], p->to, tk));
            }
        }
    }
}
int main() {
	int n, m, x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		e = 0;
		for (int i = 0; i <= n; i++)
            adj[i] = NULL;
        for (int i = 0; i < m; i++) {
        	scanf("%d %d %d", &x, &y, &w);
        	addEdge(x, y, w);
        	addEdge(y, x, w);
        }
        dijkstra(1, dist, n);
        if (dist[n][0] != INF)
        	printf("%lld\n", dist[n][0]);
        else
        	puts("-1");
	}
	return 0;
}
/*
4 4
1 2 2
2 3 1
2 4 10
3 4 6
*/ 
