#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <map>
using namespace std;

const int MAXV = 20010;
const int MAXE = MAXV * 300 * 2;
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
        assert(x < MAXV && y < MAXV);
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

int visited[32767], N, L;
vector<int> D;
void dfs(int u) {
	if (visited[u])	return ;
	visited[u] = 1, D.push_back(u);
	for (int i = 0; (1<<i) <= u; i++)	 {
		if ((u>>i)&1) {
			int v = u + (1<<i);
			if (v <= L) {
				dfs(v);
				g.Addedge(u, v + L, 1);
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int x, y, u, v;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &L);
		assert(N > 0 && N <= 36);
		memset(visited, 0, sizeof(visited));
		D.clear();
		int A[10000 + 5];
		int source = 0, sink = 2 * L + 1;
        g.Init(2 * L + 5);
		for (int i = 0; i < N; i++) {
			scanf("%d", &A[i]);
			dfs(A[i]);
		}
		for (int i = 0; i < D.size(); i++) {
			g.Addedge(source, D[i], 1);
			g.Addedge(D[i] + L, sink, 1);
		}
        int ret = D.size() - g.Maxflow(source, sink);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
} 
/*
99999
1 36
20
2 40
8 20
1 2
2
1 10
6
*/ 
 
