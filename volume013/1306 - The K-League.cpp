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
        assert(n < MAXV);
        for (int i = 0; i < n; ++i) adj[i] = NULL;
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


int n;
int w[32], a[32][32];
int valid(int x) {
	int win = w[x];
	for (int i = 1; i <= n; i++)
		win += a[x][i];

	int source = 0, sink = n+n*(n-1)/2+1;
	int aid = n+1, tot = 0;
	g.Init(sink+1);
	for (int i = 1; i <= n; i++) {
		if (w[i] > win)
			return 0;
		g.Addedge(i, sink, win-w[i]);
		for (int j = i+1; j <= n; j++) {
			tot += a[i][j];
			g.Addedge(source, aid, a[i][j]);
			g.Addedge(aid, i, a[i][j]);
			g.Addedge(aid, j, a[i][j]);
			aid++;
		}
	}
	
	int flow = g.Maxflow(source, sink);
	return flow == tot;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		for (int i = 1; i <= n; i++)
			scanf("%d %*d", &w[i]);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);
		}

		for (int i = 1, f = 0; i <= n; i++) {
			if (valid(i)) {
				if (f)	putchar(' ');
				printf("%d", i);
				f = 1;
			}
		}
		puts("");
	}
	return 0;
}
/*
3
3
2 0 1 1 0 2
0 2 2 2 0 2 2 2 0
3
4 0 2 2 0 4
0 1 1 1 0 1 1 1 0
4
0 3 3 1 1 3 3 0
0 0 0 2 0 0 1 0 0 1 0 0 2 0 0 0
*/
