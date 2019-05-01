#include <bits/stdc++.h>
using namespace std;
const int MAXV = 4096;
const int MAXE = MAXV * 200 * 2;
typedef struct Edge {
    int v, cap, cost;
    Edge *next, *re;
} Edge;
class MinCost {
public:
    const int INF = 0x3f3f3f3f;
    Edge edge[MAXE], *adj[MAXV], *arc[MAXV];
    int e, n, st, ed;
    int8_t inq[MAXV];
	int mncost, mxflow, dist[MAXV];
    queue<int> Q;
    void Addedge(int x, int y, int cap, int cost) {
        edge[e].v = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = adj[x], edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = adj[y], edge[e].re = &edge[e-1], adj[y] = &edge[e++];
    }
	void Spfa() {
		for (int i = 0; i <= n; i++)
			inq[i] = 0, dist[i] = INF;
			
		dist[st] = 0, inq[st] = 1;
		Q.push(st);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			inq[u] = 0;
			for (Edge *i = adj[u]; i != NULL; i = i->next) {
				if (i->cap == 0 || dist[i->v] <= dist[u] + i->cost)
					continue;
				dist[i->v] = dist[u] + i->cost;
				if (!inq[i->v]) {
					inq[i->v] = 1;
					Q.push(i->v);
				}
			}
		}
		
		int ded = dist[ed];
		for (int i = 0; i <= n; i++)
			dist[i] = ded - dist[i];
	}
	int Adjust() {
		int mn = INF;
		for (int i = 0; i < n; i++) {
			if (inq[i] == 0)
				continue;
			for (Edge *p = adj[i]; p != NULL; p = p->next) {
				if (p->cap == 0)
					continue;
				if (inq[p->v] == 0 && dist[p->v] - dist[i] + p->cost < mn)
					mn = dist[p->v] - dist[i] + p->cost;
			}
		}
		if (mn == INF)
			return 0;
		for (int i = 0; i <= n; i++) {
			if (inq[i])
				arc[i] = adj[i], inq[i] = 0, dist[i] += mn;
		}
		return 1;
	}
	int Augment(int i, int flow) {
		if (i == ed) {
			mncost += dist[st] * flow;
			mxflow += flow;
			return flow;
		}

		inq[i] = 1;
		for (Edge *p = arc[i]; p != NULL; p = p->next) {
			if (p->cap == 0)
				continue;
			if (inq[p->v] || dist[p->v] + p->cost != dist[i])
				continue;
			int delta = Augment(p->v, min(flow, p->cap));
			if (delta) {
				p->cap -= delta;
				p->re->cap += delta;
				arc[i] = p;
				return delta;
			}
		}
		return 0;
	}
    pair<int, int> Mincost(int s, int t) {
    	st = s, ed = t;
        Spfa();
        mncost = 0, mxflow = 0;
        for (int i = 0; i < n; i++)	arc[i] = adj[i];
        
        do {
        	do {
        		memset(inq, 0, sizeof(inq[0])*n);
			} while (Augment(st, INF));
		} while (Adjust());
        return {mncost, mxflow};
    }
    void Init(int x) {
    	n = x, e = 0;
        assert(n < MAXV);
        for (int i = 0; i < n; ++i) adj[i] = NULL;
    }
} g;

int main() {
	int cases = 0;
	int n, a, b;
	char s[64][64];
	while (scanf("%d %d %d", &n, &a, &b) == 3 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);

		int placed = 0;
		int row[64] = {}, col[64] = {}, tot = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (s[i][j] == 'C')
					placed++;
				if (s[i][j] != '/')
					row[i]++, col[j]++, tot++;
			}
		}
		
		printf("Case %d: ", ++cases);
		
		int ret = -1;
		for (int limit = n; limit >= 0; limit--) {
			int source = 2*n, sink = 2*n+1;
			g.Init(2*n+2);
			
			for (int i = 0; i < n; i++) {
				g.Addedge(source, i, row[i], 0);
				g.Addedge(i+n, sink, col[i], 0);
				g.Addedge(i, i+n, limit, 0);		// pass this edge presents the placed number of i-th row/col.
				for (int j = 0; j < n; j++) {
					if (s[i][j] == '.')
						g.Addedge(i, j+n, 1, 1);	// pass this edge presents (i, j) unplaced.
				}
			}
			
			auto cost = g.Mincost(source, sink);
			if (cost.second == tot) {
				int added = tot - cost.first;
				// limit/placed <= a/b
				if (added * a >= limit * b) {
					ret = added - placed;
					break;
				}
			}
		}
		
		if (ret < 0)
			printf("impossible\n");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
2 1 1
/.
//
2 50 100
/.
C/
2 100 100
./
C.
5 3 10
CC/..
././/
..C.C
/.C..
/./C/
5 2 10
CC/..
././/
..C.C
/.C..
/./C/
0 0 0
*/

