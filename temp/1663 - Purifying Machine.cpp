#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;
// at most one switch can be turned to state '*'
// bipartite graph, maximum matching
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

vector<int> D;          // different
int color[1024] = {};
int main() {
    for (int i = 0; i < 1024; i++) { // graph
        for (int j = 0; j < i; j++) {
            if (__builtin_popcount(i^j) == 1) {
                color[i] = !color[j];
                break;
            }
        }
    }
    int n, m;
    char s[16];
    while (scanf("%d %d", &m, &n) == 2 && m) {
        D.clear();
        
        int used[1024] = {};
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            int val = 0, star = -1;
            for (int j = 0; j < m; j++) {
                if (s[j] == '*') {
                    star = 1<<j;
                } else {
                    val |= (s[j] - '0')<<j;
                }
            }
            if (star >= 0) {
                D.push_back(val), D.push_back(val + star);
            } else {
                D.push_back(val);
            }
        }
        sort(D.begin(), D.end());
        D.resize(unique(D.begin(), D.end()) - D.begin());
        
        for (int i = 0; i < D.size(); i++)
            used[D[i]] = 1;
        
        g.Init(1024 + 5);
        int source = 1024, sink = 1024 + 1;
        for (int i = 0; i < D.size(); i++) {
            if (color[D[i]] == 0) {
                for (int j = 0; j < m; j++) {
                    if (used[D[i]^(1<<j)])
                        g.Addedge(D[i], D[i]^(1<<j), 1);
                }
                g.Addedge(source, D[i], 1);
            } else {
                g.Addedge(D[i], sink, 1);
            }
        }
        
        int ret = (int) D.size() - g.Maxflow(source, sink);
        printf("%d\n", ret);
    }
    return 0;
}
/*
 3 3
 *01
 100
 011
 0 0
 */
