// bipartite matching, maxflow
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

int main() {
    int N, x, y;
    char s[128][128];
    while (scanf("%d", &N) == 1) {
    	for (int i = 0; i < N; i++)
    		scanf("%s", &s[i]);
    	int R[128][128], C[128][128];
    	int rcnt = 0, ccnt = 0;
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
    			if (s[i][j] == '.' && (j == 0 || s[i][j-1] == 'X'))
    				rcnt++;
    			if (s[i][j] == '.')
    				R[i][j] = rcnt;
    		}
    	}
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
    			if (s[j][i] == '.' && (j == 0 || s[j-1][i] == 'X'))
    				ccnt++;
    			if (s[j][i] == '.')
    				C[j][i] = ccnt;
    		}
    	}
    	g.Init(rcnt + ccnt + 2);
    	int source = 0, sink = rcnt + ccnt + 1;
    	for (int i = 0; i < N; i++) {
    		for (int j = 0; j < N; j++) {
    			if (s[i][j] == '.')
    				g.Addedge(R[i][j], C[i][j] + rcnt, 1);
    		}
    	}
    	for (int i = 1; i <= rcnt; i++)
    		g.Addedge(source, i, 1);
    	for (int i = 1; i <= ccnt; i++)
    		g.Addedge(i + rcnt, sink, 1);
    	int ret = g.Maxflow(source, sink);
        printf("%d\n", ret);
    }
    return 0;
}
/*
 */

