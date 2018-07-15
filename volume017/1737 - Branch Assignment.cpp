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

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int main() {
	int n, b, s, r;
//	while (scanf("%d %d %d %d", &n, &b, &s, &r) == 4) {
	while (ReadInt(&n)) {
		ReadInt(&b), ReadInt(&s), ReadInt(&r);
		e = 0;
		for (int i = 0; i <= n; i++)
			adj[i] = NULL;
		for (int i = 0; i < r; i++) {
			int x, y, w;
//			scanf("%d %d %d", &x, &y, &w);
			ReadInt(&x), ReadInt(&y), ReadInt(&w);
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
		for (int i = 0; i <= s; i++)
			dp[i][0] = INF;
		dp[0][0] = 0;
		
		for (int i = 1; i <= b; i++) {
			dp[0][i] = INF;
			
			static int64_t tmp[MAXV];
			for (int j = 1; j <= i; j++)
				tmp[j] = (j-1) * (sum[i] - sum[i-j]);
			for (int j = 1; j <= i && j <= s; j++) {
				int64_t v = INF;
				for (int k = 1, l = i/j; k <= l; k++)
					v = min(v, dp[j-1][i-k] + tmp[k]);
				dp[j][i] = v;
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
