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
    pair<int, int> Mincost(int s, int t, int runSPFA = 1) {
    	st = s, ed = t;
    	if (runSPFA)
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


int n, m;
char s[64][64];

void test(int x, int &ret) {
	if (x*n%m)
		return ;
	int y = x*n/m;
	int source = n+m, sink = n+m+1;
	int ones = 0;

	g.Init(n+m+2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '1') {
				ones++;
				g.Addedge(i, n+j, 1, -1);
			} else {
				g.Addedge(i, n+j, 1, 1);
			}
		}
	}
	
	if (x == 0) {
		ret = min(ret, ones);
		return ;
	}
	
	for (int i = 0; i < n; i++)
		g.Addedge(source, i, x, 0);
	for (int i = 0; i < m; i++)
		g.Addedge(i+n, sink, y, 0);

	static int dist[MAXV];
	if (x == m) {
		g.st = source, g.ed = sink;
		g.Spfa();
		for (int i = 0; i <= g.n; i++)
			dist[i] = g.dist[i];
	} else {
		for (int i = 0; i <= g.n; i++)
			g.dist[i] = dist[i];
	}
	auto cost = g.Mincost(source, sink, 0);
	ret = min(ret, cost.first + ones);
}

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		
		int ret = n*m;
		for (int i = m; i >= 0; i--)
			test(i, ret);
		
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3
2 3
111
111
3 3
011
011
011
2 3
001
000
*/
