#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
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

int army[128], n;
char s[128][128];
int testValidBorder(int border_army) {
	g.Init(2 * n + 2);
	int source = 2*n, sink = 2*n + 1;
	int full_flow = 0, INF = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		if (army[i] > 0) {
			g.Addedge(source, 2*i, army[i]);
			g.Addedge(2*i, 2*i+1, INF);
			int ok = 0;
			for (int j = 0; j < n; j++) {
				if (s[i][j] == 'Y' && army[j] == 0)
					ok = 1;
				if (s[i][j] == 'Y' && army[j] > 0)
					g.Addedge(2*i, 2*j+1, INF);
			}
			if (ok) { 	// border
				g.Addedge(2*i+1, sink, border_army);
				full_flow += border_army;
			} else { 	// not border, each region must contain at least one army.
				g.Addedge(2*i+1, sink, 1);
				full_flow += 1;
			}
		}
	}
	
	int flow = g.Maxflow(source, sink);
//	printf("%d %d %d\n", flow, full_flow, border_army);
	return flow == full_flow;
}
int main()  {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &army[i]);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		
		int border = 0, sum_army = 0;
		for (int i = 0; i < n; i++) {
			if (army[i] > 0) {
				int ok = 0;
				for (int j = 0; j < n; j++) {
					if (s[i][j] == 'Y' && army[j] == 0)
						ok = 1;
				}
				sum_army += army[i], border += ok;
			}
		}
		
		int l = 0, r = sum_army / border, mid;
		int ret = 0;
		while (l <= r) {
			mid = (l+r)/2;
			if (testValidBorder(mid))
				l = mid + 1, ret = mid;
			else
				r = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
