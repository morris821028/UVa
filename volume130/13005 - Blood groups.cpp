#include <bits/stdc++.h>
using namespace std;

const int MAXV = 40010;
const int MAXE = MAXV * 200 * 2;
const int INF = 1<<29;
typedef struct Edge {
    int v, cap, flow;
    Edge *next, *re;
} Edge;
class MaxFlow {
    public:
    Edge edge[MAXE], *adj[MAXV], *pre[MAXV], *arc[MAXV];
    int e, n, level[MAXV], lvCnt[MAXV], Q[MAXV];
    void Init(int x) {
        n = x, e = 0;
        for (int i = 0; i < n; ++i) adj[i] = NULL;
    }
    void Addedge(int x, int y, int flow){
        edge[e].v = y, edge[e].cap = flow, edge[e].next = adj[x];
        edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].next = adj[y];
        edge[e].re = &edge[e-1], adj[y] = &edge[e++];
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
} g;
int main() {
	int N, Q, B, x;
	while (scanf("%d %d", &N, &Q) == 2) {
		set< set<int> > S;
		set<int> A[128];
		for (int i = 0; i < N; i++) {
			scanf("%d", &B);
			for (int j = 0; j < B; j++) {
				scanf("%d", &x);
				A[i].insert(x);
			}
			if (B != N)	A[i].insert(0);
		}
		
		for (int i = 0; i < Q; i++) {			
			int source = 2*N+2, sink = 2*N+3;
			g.Init(2*N+5);
			
			int used[128] = {};
			for (int j = 0; j < N; j++)	// parent
				g.Addedge(source, j, 1);
				
			scanf("%d", &B);
			for (int j = 0; j < B; j++) {
				scanf("%d", &x);
				g.Addedge(N+x, sink, 1);
				for (int k = 0; k < N; k++) {
					if (A[k].count(x)) {
						g.Addedge(k, N+x, 1);
						used[k] = 1;
					}
				}
			}
			
			int allused = 1;
			for (int j = 0; j < N; j++) {
				if (A[j].count(0) && B != N)
					used[j] = 1;
				allused &= used[j];
			}
			
			if (!allused) {
				puts("N");
				continue;
			}
			
			int flow = g.Maxflow(source, sink);
			puts(flow == B ? "Y" : "N");
		}
	}
	return 0;
}

