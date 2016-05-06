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
	scanf("%d", &testcase);
	while (testcase--) {
		int M, N, K;
		int W[64], V[64], R[64];
		vector<int> WR[64];
		int sumVIP = 0, maxW = 0;
		scanf("%d %d %d", &M, &N, &K);
		for (int i = 0; i < N; i++)
			scanf("%d", &W[i]), maxW = max(maxW, W[i]);
		for (int i = 0; i < M; i++) {
			int n, x;
			scanf("%d %d %d", &V[i], &R[i], &n);
			WR[i].clear();
			for (int j = 0; j < n; j++) {
				scanf("%d", &x), x--;
				WR[i].push_back(x);
			}
			sumVIP += V[i];
		}
		
		long long l = 0, r = (long long) maxW * (sumVIP + K), mid, ret = 0;
		while (l <= r)  {
			mid = (l + r)/2;
			
			long long time = mid;
			int source = N + 2*M;
			int sink1 = N + 2*M + 1;	// VIP
			int sink2 = N + 2*M + 2;	// Regular
			int sink = N + 2*M + 3;
			g.Init(N + 2*M + 5);
			for (int i = 0; i < N; i++) {
				g.Addedge(source, i, time / W[i]);
//				printf("e %d %d %d\n", source, i, time / W[i]);
			}
			g.Addedge(sink1, sink, sumVIP);
			g.Addedge(sink2, sink, K);
//			printf("e %d %d %d\n", sink1, sink, sumVIP);
//			printf("e %d %d %d\n", sink2, sink, K);
			for (int i = 0; i < M; i++) {
				int u1 = N + 2*i, u2 = N + 2*i + 1;
				g.Addedge(u1, sink1, V[i]);
				g.Addedge(u2, sink2, R[i]);
//				printf("e %d %d %d\n", u1, sink1, V[i]);
//				printf("e %d %d %d\n", u2, sink2, R[i]);
				for (int j = 0; j < WR[i].size(); j++) {
					int v = WR[i][j];
//					printf("e %d %d %d\n", v, u1, INF);
//					printf("e %d %d %d\n", v, u2, INF);
					g.Addedge(v, u1, LLINF);
					g.Addedge(v, u2, LLINF);
				}
			}
			
			long long flow = g.Maxflow(source, sink);
//			printf("time %d: %d\n", time, flow);
			if (flow == sumVIP + K)
				r = mid - 1, ret = time;
			else
				l = mid + 1;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

