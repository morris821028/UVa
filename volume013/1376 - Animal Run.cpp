#include <bits/stdc++.h> 
using namespace std;

enum TRI {UP, DOWN};
int n, m, st, ed;
int labeling(int x, int y, TRI t) {
	if (x < 0 || y >= m-1)	return ed;
	if (y < 0 || x >= n-1)	return st;
	if (t == UP)
		return (x*(m-1)+y)*2;
	if (t == DOWN)
		return (x*(m-1)+y)*2+1;
	assert(false);
}

const int MAXV = 1048576*2;
const int MAXE = MAXV*8;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to, eid;
    int w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
int dist[MAXV];
void addEdge(int x, int y, int v)  {
    edge[e].to = y, edge[e].w = v, edge[e].eid = e;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, int ed, int dist[], int n) {
    typedef pair<int, int> PLL;
    for (int i = 0; i <= n; i++)
        dist[i] = INF;
    set<PLL> pQ;
    PLL u;
    pQ.insert(PLL(0, st)), dist[st] = 0;
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        if (u.second == ed)
        	return ;
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
void init(int n) {
	e = 0;
	memset(adj, 0, sizeof(adj[0])*n);
} 
int main() {
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		init(n*m*2+2);		
		st = n*m*2, ed = n*m*2+1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m-1; j++) {
				int w, u, v;
				scanf("%d", &w);
				u = labeling(i, j, UP), v = labeling(i-1, j, DOWN);
				addEdge(u, v, w), addEdge(v, u, w);
			}
		}
		
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < m; j++) {
				int w, u, v;
				scanf("%d", &w);
				u = labeling(i, j, DOWN), v = labeling(i, j-1, UP);
				addEdge(u, v, w), addEdge(v, u, w);
			}
		}
		
		for (int i = 0; i < n-1; i++) {
			for (int j = 0; j < m-1; j++) {
				int w, u, v;
				scanf("%d", &w);
				u = labeling(i, j, DOWN), v = labeling(i, j, UP);
				addEdge(u, v, w), addEdge(v, u, w);
			}
		}
		
		dijkstra(st, ed, dist, n*m*2+2); 
		printf("Case %d: Minimum = %d\n", ++cases, dist[ed]);
	}
	return 0;
}
