#include <bits/stdc++.h>
using namespace std;
const int MAXV = 64;
const int MAXE = MAXV * 200 * 2;
const int INF = 1<<29;
typedef struct Edge {
    int v, cap, flow;
    Edge *next, *re;
} Edge;
class MaxFlow {
    public:
    Edge edge[MAXE], *adj[MAXV], *pre[MAXV], *arc[MAXV];
    int e, n, level[MAXV], lvCnt[MAXV], Q[MAXV], ban[MAXV];
    void Init(int x) {
        n = x, e = 0;
        assert(n < MAXV);
        for (int i = 0; i < n; ++i) adj[i] = NULL, ban[i] = 0;
    }
    void AddBiedge(int x, int y, int flow){
        edge[e].v = y, edge[e].cap = flow, edge[e].next = adj[x];
        edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = flow, edge[e].next = adj[y];
        edge[e].re = &edge[e-1], adj[y] = &edge[e++];
        assert(e < MAXE);
    }
    void Addedge(int x, int y, int flow){
        edge[e].v = y, edge[e].cap = flow, edge[e].next = adj[x];
        edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].next = adj[y];
        edge[e].re = &edge[e-1], adj[y] = &edge[e++];
        assert(e < MAXE);
    }
    void Bfs(int v){
        int front = 0, rear = 0, r = 0, dis = 0;
        for (int i = 0; i < n; ++i) level[i] = n, lvCnt[i] = 0;
        level[v] = 0, ++lvCnt[0];
        Q[rear++] = v;
        while (front != rear){
            if (front == r) ++dis, r = rear;
            v = Q[front++];
            for (Edge *i = adj[v]; i != NULL; i = i->next) {
                int t = i->v;
                if (ban[t])
                	continue;
                if (level[t] == n) level[t] = dis, Q[rear++] = t, ++lvCnt[dis];
            }
        }
    }
    int Maxflow(int s, int t){
        int ret = 0, i, j;
        Bfs(t);
        for (i = 0; i < n; ++i) pre[i] = NULL, arc[i] = adj[i];
        for (i = 0; i < e; ++i) edge[i].flow = edge[i].cap;
        i = s;
        while (level[s] < n){
            while (arc[i] && (level[i] != level[arc[i]->v]+1 || !arc[i]->flow)) 
                arc[i] = arc[i]->next;
            if (arc[i]){
                j = arc[i]->v;
                pre[j] = arc[i];
                i = j;
                if (i == t){
                    int update = INF;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        if (update > p->flow) update = p->flow;
                    ret += update;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        p->flow -= update, p->re->flow += update;
                    i = s;
                }
            }
            else{
                int depth = n-1;
                for (Edge *p = adj[i]; p != NULL; p = p->next)
                    if (p->flow && depth > level[p->v]) depth = level[p->v];
                if (--lvCnt[level[i]] == 0) return ret;
                level[i] = depth+1;
                ++lvCnt[level[i]];
                arc[i] = adj[i];
                if (i != s) i = pre[i]->re->v;
            }
        }
        return ret;
    }
    void Erase(int t) {
    	ban[t] = 1;
	}
} g;

int main() {
	int n, m, cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		g.Init(n+2);
		int mid = n+1;
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g.AddBiedge(u, v, 1);
		}

		int ret = 0;
		int dist[MAXV];
		for (int i = 0; i <= n; i++)
			dist[i] = INF;
		set<pair<int, int>> pQ;
		dist[0] = 0;
		pQ.insert({0, 0}), dist[0] = 0;
		while (!pQ.empty()) {
			auto u = *pQ.begin();
			if (u.second == 1)
				break;
			pQ.erase(pQ.begin());
			for (int i = 1; i <= n; i++) {
				if (dist[i] == u.first)
					g.Erase(i);
			}
			for (int i = 0; i <= n; i++) {
				if (dist[i] <= dist[u.second])
					continue;
				int c = g.Maxflow(0, i);
				if (dist[i] > dist[u.second] + c) {
					if (dist[i] != INF)
						pQ.erase(pQ.find({dist[i], i}));
					dist[i] = dist[u.second] + c;
					pQ.insert({dist[i], i});
				}
			}
		}
		printf("Case %d: %d\n\n", ++cases, dist[1]);
	}
	return 0;
}
/*
4  6
1  2
1  3
2  4
3  4
4  0
4  0

4  6
1  2
1  3
1  4
2  0
3  0
4  0

4  5
1  2
1  3
1  4
2  0
3  0

0  0
*/
