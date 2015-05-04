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
} maxflow;

vector< pair<int, int> > g[MAXV];
int dist[MAXV], inq[MAXV];
void spfa(int st, int n) {
	queue<int> Q;
	int u, v; 
	
	for (int i = 0; i <= n; i++)
		dist[i] = 0x3f3f3f3f, inq[i] = 0;
	Q.push(st), dist[st] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].first;
			if (dist[v] > dist[u] + g[u][i].second) {
				dist[v] = dist[u] + g[u][i].second;
				if (!inq[v])
					inq[v] = 0, Q.push(v);
			}
		}
	}
}

const int MAXM = 131072;
int X[MAXM], Y[MAXM], T[MAXM], C[MAXM];
int main() {
	int n, m, c;
	while (scanf("%d %d %d", &n, &m, &c) == 3) {
		for (int i = 1; i <= n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &X[i], &Y[i], &T[i]);
			g[X[i]].push_back(make_pair(Y[i], T[i]));
			g[Y[i]].push_back(make_pair(X[i], T[i]));
		}
		
		for (int i = 0; i < c; i++)
			scanf("%d", &C[i]);
			
		spfa(1, n); 
		
		// shortest path as DAG
		int m_cnt = 0;
		for (int i = 0; i < m; i++) {
			int u = X[i], v = Y[i];
			if (dist[u] == dist[v] + T[i] || dist[v] == dist[u] + T[i]) {
				X[m_cnt] = X[i], Y[m_cnt] = Y[i], T[m_cnt] = T[i];
				m_cnt++;
			}
		}
		m = m_cnt; // #remain edge
		
		vector< pair<int, int> > D;
		for (int i = 0; i < c; i++)
			D.push_back(make_pair(dist[C[i]], C[i]));
		sort(D.begin(), D.end());
		
		// only commuters which are the same distance from position to downtown occur collision.
		int ret = 0;
		for (int i = 0; i < c; i++) {
			maxflow.Init(n + 2);
			
			int source = n + 1, sink = 1;
			int j = i;
			while (j < c && D[j].first == D[i].first)
				maxflow.Addedge(source, D[j].second, 1), j++;
			i = j-1;
			
			for (int j = 0; j < m; j++) {
				int u = X[j], v = Y[j];
				if (dist[u] == dist[v] + T[j])
					maxflow.Addedge(u, v, 1);
				if (dist[v] == dist[u] + T[j])
					maxflow.Addedge(v, u, 1);
			}
			
			int t = maxflow.Maxflow(source, sink);
			ret += t;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3 3 2
1 2 42
2 3 1
2 3 1
2 3

4 4 5
1 2 5
1 3 4
4 2 5
4 3 6
4 4 4 4 1
*/
