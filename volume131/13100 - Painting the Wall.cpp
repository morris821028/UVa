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
const int MAXN = 1024*1024;
int mx[MAXN], my[MAXN];
int X[MAXN], Y[MAXN];
int n, m, VX, VY;
int C[MAXN][3], R[MAXN][3];
void dfs(int u) {
	if (X[u])	return ;
	X[u] = 1;
	for (Edge *p = g.adj[u]; p != NULL; p = p->next) {
		if (p->v - VX >= 1 && p->v - VX <= VY) {
			if (my[p->v - VX] != -1 && Y[p->v - VX] == 0) {
				Y[p->v - VX] = 1;
				dfs(my[p->v - VX]);
			}
		}
	}
}
int main() {
    static char s[1024][1024];
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++)
        	scanf("%s", s[i]+1);
        
        static int xg[1024][1024] = {};
        static int yg[1024][1024] = {};
        memset(xg, 0, sizeof(xg));
        memset(yg, 0, sizeof(yg));
        VX = 0, VY = 0;
        for (int i = 1; i <= n; i++) {
        	for (int j = 1; j <= m; j++) {
        		if (s[i][j] == '*') {
        			if (xg[i][j] == 0) {
        				xg[i][j] = ++VX;
        				int k = j;
        				while (k <= m && s[i][k] == '*')
        					xg[i][k] = VX, k++;
        				C[VX][0] = i, C[VX][1] = j, C[VX][2] = k-1;
					}
					if (yg[i][j] == 0) {
						yg[i][j] = ++VY;
						int k = i;
						while (k <= n && s[k][j] == '*')
							yg[k][j] = VY, k++;
						R[VY][0] = j, R[VY][1] = i, R[VY][2] = k-1;
					}
				}
			}
		}
		
		int source = 0, sink = VX+VY+1;
		g.Init(VX+VY+2);
		for (int i = 1; i <= VX; i++)
			g.Addedge(source, i, 1);
		for (int i = 1; i <= VY; i++)
			g.Addedge(VX+i, sink, 1);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (s[i][j] == '*') {
//					printf("%d - %d\n", xg[i][j], yg[i][j]);
					g.Addedge(xg[i][j], yg[i][j] + VX, 1);
				}
			}
		}
		int mxflow = g.Maxflow(source, sink);
		memset(mx, -1, sizeof(mx));
		memset(my, -1, sizeof(my));
		memset(X, 0, sizeof(X));
		memset(Y, 0, sizeof(Y));
		int match = 0;
		for (int i = 1; i <= VX; i++) {
            for (Edge *p = g.adj[i]; p != NULL; p = p->next) {
                int x = i, y = p->v, flow = p->flow;
                if (flow == 0 && y - VX >= 1 && y - VX <= VY) {
                    // match x - (y - VX) in bipartite graph
                    int r = x, c = y - VX;
                    mx[r] = c;
                    my[c] = r;
                    match++;
                }
            }
        }
        assert(match == mxflow);
        
		for (int i = 1; i <= VX; i++) {
			if (mx[i] == -1)
				dfs(i);
		}
		
		printf("%d\n", mxflow);
		for (int i = 1; i <= VX; i++) {
			if (!X[i] && mx[i] != -1) {
				printf("hline %d %d %d\n", C[i][0], C[i][1], C[i][2]);
				mxflow--;
			}
		}
		for (int i = 1; i <= VY; i++) {
			if (Y[i]) {
				printf("vline %d %d %d\n", R[i][0], R[i][1], R[i][2]);
				mxflow--;
			}
		}
		assert(mxflow == 0);
    }
    return 0;
}
