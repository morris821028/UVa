#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1024;
const int MAXE = 131072;
const long long INF = 1LL<<60;
struct Edge {
    int to, eid;
    long long w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
double dist[MAXV];
void addEdge(int x, int y, long long v)  {
    edge[e].to = y, edge[e].w = v, edge[e].eid = e;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st[], int m, long long dist[], int n) {
    typedef pair<long long, int> PLL;
    for (int i = 0; i <= n; i++)
        dist[i] = INF;
    set<PLL> pQ;
    PLL u;
    for (int i = 0; i < m; i++)
    	pQ.insert(PLL(0, st[i])), dist[st[i]] = 0;
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
	int N, M, B, P;
	while (scanf("%d %d %d %d", &N, &M, &B, &P) == 4) {
		e = 0;
		for (int i = 0; i <= N; i++)
			adj[i] = NULL;
        for (int i = 0; i < M; i++) {
			int u, v, t;
        	scanf("%d %d %d", &u, &v, &t);
        	addEdge(u, v, t);
        	addEdge(v, u, t);
		}
		int b[1024] = {}, p[1024];
		long long dist[1024];
		for (int i = 0; i < B; i++) {
			int x;
			scanf("%d", &x);
			b[x] = 1;
		}
		for (int i = 0; i < P; i++)
			scanf("%d", &p[i]);
		dijkstra(p, P, dist, N);
		
		long long mxv = 0;
		int mxc = 0;
		for (int i = 0; i < N; i++) {
			if (b[i])
				mxv = max(mxv, dist[i]);
		}
		for (int i = 0; i < N; i++) {
			if (b[i])
				mxc += mxv == dist[i];
		}
		if (mxv == INF)
			printf("%d *\n", mxc);
		else
			printf("%d %lld\n", mxc, mxv);
		for (int i = 0; i < N; i++) {
			if (mxv == dist[i] && b[i]) {
				mxc--;
				printf("%d%c", i, mxc ? ' ' : '\n');
			}
		}
	}
	return 0;
}
/*
5 6 2 1
0 1 5
0 2 2
1 3 6
1 4 1
2 3 4
3 4 3
1 4
2
5 4 2 1
0 1 5
0 2 2
1 3 6
2 3 4
1 4
2
5 6 2 2
0 1 5
0 2 2
1 3 6
1 4 1
2 3 4
3 4 3
1 4
2 3
*/
