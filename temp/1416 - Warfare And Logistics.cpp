#include <stdio.h> 
#include <vector>
#include <queue> 
#include <algorithm>
using namespace std;
typedef struct Edge {
    int v, w, eid;
    Edge *next, *re;
} Edge;
typedef pair<int, int> PII;
const int MAXV = 128;
const int MAXE = MAXV * 200 * 2;
class Dijkstra {
    public:
    Edge edge[MAXE], *adj[MAXV], *pre[MAXV];
    int e, n, INF;
    int dist[MAXV];
    void Init(int x, int inf) {
        n = x, e = 0, INF = inf;
        for (int i = 0; i < n; ++i) adj[i] = NULL;
    }
    void Addedge(int x, int y, int w) {
    	int id = e/2;
        edge[e].v = y, edge[e].w = w, edge[e].next = adj[x];
        edge[e].eid = id, edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].w = w, edge[e].next = adj[y];
        edge[e].eid = id, edge[e].re = &edge[e-1], adj[y] = &edge[e++];
    }
    void dijkstra(int st, Edge *ban) {
        priority_queue<PII, vector<PII>, greater<PII> > pQ;
        for (int i = 0; i < n; i++)
        	dist[i] = INF, pre[i] = NULL;
        dist[st] = 0;
        pQ.push(PII(0, st));
        while (!pQ.empty()) {
        	PII u = pQ.top();
        	pQ.pop();
        	if (u.first > dist[u.second])
        		continue;
        	for (Edge *p = adj[u.second]; p != NULL; p = p->next) {
        		if (ban != NULL && (p == ban || p == ban->re))
        			continue;
        		if (dist[p->v] > dist[u.second] + p->w) {
        			dist[p->v] = dist[u.second] + p->w;
        			pre[p->v] = p;
        			pQ.push(PII(dist[p->v], p->v));
        		}
        	}
        }
    }
} g;
int n, m, L, x, y, v;
int main() {
	const int INF = 0x3f3f3f3f;
	while (scanf("%d %d %d", &n, &m, &L) == 3) {
		g.Init(n, INF);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &v);
			x--, y--;
			g.Addedge(x, y, v);
		}
		
		long long ret = 0, origin[MAXV], damage[2048];
		int exist[2048];
		Edge *pre[MAXV];
		
		for (int i = 0; i < m; i++)
			damage[i] = 0;
		
		for (int i = 0; i < n; i++) {
			g.dijkstra(i, NULL);
			
			long long sum = 0;
			for (int j = 0; j < n; j++) {
				sum += g.dist[j] == INF ? L : g.dist[j];
				pre[j] = g.pre[j];
			}
			ret += sum, origin[i] = sum;
			
			for (int j = 0; j < m; j++)
				exist[j] = 0;
			for (int j = 0; j < n; j++) {
				if (pre[j] == NULL)
					continue;
				// edge on shortest path tree.
				g.dijkstra(i, pre[j]);
				
				long long tmp = 0;
				for (int k = 0; k < n; k++)
					tmp += g.dist[k] == INF ? L : g.dist[k];
				damage[pre[j]->eid] += tmp;
				exist[pre[j]->eid] = 1;
			} 
			for (int j = 0; j < m; j++) {
				if (!exist[j])
					damage[j] += origin[i];
			}
		}
		
		long long mxDamage = ret;
		for (int i = 0; i < m; i++)
			mxDamage = max(mxDamage, damage[i]);
		printf("%lld %lld\n", ret, mxDamage);
	}
	return 0;
}
/*
4  6  1000
1  3  2
1  4  4
2  1  3
2  3  3
3  4  1
4  2  2
*/
