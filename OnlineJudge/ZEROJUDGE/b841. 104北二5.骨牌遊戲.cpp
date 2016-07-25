#include <bits/stdc++.h>
using namespace std;

const int MAXV = 3005;
const int MAXE = MAXV * 10 * 2;
const long long LLINF = 1LL<<62;
typedef struct Edge {
    int v;
    long long cap, flow;
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
    void Addedge(int x, int y, long long flow){
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
    long long Maxflow(int s, int t){
        long long ret = 0;
        int i, j;
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
                    long long update = LLINF;
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
	int n, m;
	int s[128][128] = {};
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%d", &s[i][j]);
		}
		
		g.Init(n*m+2);
		int source = n*m, sink = n*m+1;
		const int dx[] = {0, 0, 1, -1};
		const int dy[] = {1, -1, 0, 0};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if ((i+j)%2) {
					g.Addedge(source, i*m+j, 1);
					for (int k = 0; k < 4; k++) {
						int tx, ty;
						tx = i+dx[k], ty = j+dy[k];
						if (tx >= 0 && ty >= 0 && tx < n && ty < m) {
							if (s[i][j] == s[tx][ty])
								g.Addedge(i*m+j, tx*m+ty, 1);
						}
					}
				} else {
					g.Addedge(i*m+j, sink, 1);
				}
			}
		}
		printf("%lld\n", g.Maxflow(source, sink));
	}
	return 0;
}
