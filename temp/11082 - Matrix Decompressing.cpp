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
    int testcase, cases = 0;
    int n, m, R[32], C[32];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &R[i]);
        for (int i = 0; i < m; i++)
            scanf("%d", &C[i]);
        
        g.Init(n + m + 2);
        int source = n + m, sink = n + m + 1;
        
        for (int i = n - 1; i >= 0; i--) {
            if (i-1 >= 0)
                R[i] -= R[i-1];
            R[i] -= m;
        }
        for (int i = m - 1; i >= 0; i--) {
            if (i-1 >= 0)
                C[i] -= C[i-1];
            C[i] -= n;
        }
        for (int i = 0; i < n; i++) {
            g.Addedge(source, i, R[i]);
        }
        for (int i = 0; i < m; i++) {
            g.Addedge(i+n, sink, C[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g.Addedge(i, n+j, 19);
            }
        }
        int flow = g.Maxflow(source, sink);
        int ret[32][32];
        for (int i = 0; i < n; i++) {
            for (Edge *p = g.adj[i]; p != NULL; p = p->next) {
                if (p->v != source)
                    ret[i][p->v - n] = p->cap - p->flow + 1;
            }
        }
        printf("Matrix %d\n", ++cases);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d%c", ret[i][j], j == m-1 ? '\n' : ' ');
            }
        }
        puts("");
    }
    return 0;
}
