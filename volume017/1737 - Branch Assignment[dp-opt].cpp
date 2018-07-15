#include <bits/stdc++.h> 
using namespace std;

const int MAXV = 5005;
const int MAXE = 131072;
const int64_t INF = 1LL<<60;
struct Edge {
    int to, w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
void addEdge(int x, int y, int v)  {
    edge[e].to = y, edge[e].w = v;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}
void dijkstra(int st, int64_t dist[], int n, int inv) {
    typedef pair<int64_t, int> PLL;
    for (int i = 0; i <= n; i++)
        dist[i] = INF;
    set<PLL> pQ;
    PLL u;
    pQ.insert(PLL(0, st)), dist[st] = 0;
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        for (Edge *p = adj[u.second]; p; p = p->next) {
        	if (((p - edge)&1) != inv)
        		continue;
            if (dist[p->to] > dist[u.second] + p->w) {
                if (dist[p->to] != INF)
                    pQ.erase(pQ.find(PLL(dist[p->to], p->to)));
                dist[p->to] = dist[u.second] + p->w;
                pQ.insert(PLL(dist[p->to], p->to));
            }
        }
    }
}

int main() {
	int n, b, s, r;
	while (scanf("%d %d %d %d", &n, &b, &s, &r) == 4) {
		e = 0;
		for (int i = 0; i <= n; i++)
			adj[i] = NULL;
		for (int i = 0; i < r; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			addEdge(x, y, w);
			addEdge(y, x, w);
		}
		
		static int64_t d_in[MAXV], d_out[MAXV];
		dijkstra(b+1, d_out, n, 0);
		dijkstra(b+1, d_in, n, 1);
		
		static int64_t d[MAXV], sum[MAXV] = {};
		for (int i = 1;  i <= b; i++)
			d[i] = d_in[i] + d_out[i];
		sort(d+1, d+b+1);
		for (int i = 1; i <= b; i++)
			sum[i] = sum[i-1] + d[i];

		static int64_t dp[MAXV][MAXV];
		static int ep[MAXV][MAXV];
		for (int i = 1; i <= b; i++)
			memset(dp[i], 0x3f, sizeof(dp[0][0])*(s+1));
		for (int i = 1; i <= b; i++) {
			dp[1][i] = (i-1) * sum[i];
			ep[1][i] = 0;
		}
		
		for (int i = 2; i <= s; i++) {
			ep[i][b+1] = b;
			for (int j = b; j >= i; j--) {
				int l = ep[i-1][j], r = ep[i][j+1], t = -1;
				int64_t v = INF;
				for (int k = l; k <= r; k++) {
					if (dp[i-1][k] + (j-k-1)*(sum[j] - sum[k]) < v) {
						v = dp[i-1][k] + (j-k-1)*(sum[j] - sum[k]);
						t = k;
					}
				}
				dp[i][j] = v;
				ep[i][j] = t;
			}
		}
		
		printf("%lld\n", dp[s][b]);
	}
	return 0;
}
/*
5  4  2  10
5  2  1
2  5  1
3  5  5
4  5  0
1  5  1
2  3  1
3  2  5
2  4  5
2  1  1
3  4  2

5 4 2 10
5  2  1
2  5  1
3  5  5
4  5  10
1  5  1
2  3  1
3  2  5
2  4  5
2  1  1
3  4  2
*/
