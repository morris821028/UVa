#include <bits/stdc++.h>
using namespace std;

const int MAXV = 40010;
const int MAXE = MAXV * 200 * 2;
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
	int testcase, cases = 0;
	int n, m;
	static int A[128], B[128], S[128], G[128][128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &A[i], &B[i], &S[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &G[i][j]);
		}
		
		int source = 2*n, sink = 2*n+1;
		int sum = 0;
		g.Init(2*n+2);
		for (int i = 0; i < n; i++) {
			int s = (S[i]+m-1)/m;
			sum += s;
			g.Addedge(source, i*2, s);
			g.Addedge(i*2+1, sink, s);
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				if (B[i]+G[i][j] < A[j])
					g.Addedge(i*2, j*2+1, LLINF);
			}
		}
		int ret = sum - g.Maxflow(source, sink);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3
1 5
1 60 12
0

4 1
1 100 10
50 130 3
150 200 15
80 170 7
0 2 3 4
5 0 7 8
9 10 0 12
13 14 15 0

2 1
1 10 1
12 20 1
0 2
5 0
*/
