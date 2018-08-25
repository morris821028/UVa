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
	int mncost, mxflow;
	int8_t dist[MAXV];
    queue<int> Q;
    void Addedge(int x, int y, int cap, int cost) {
        edge[e].v = y, edge[e].cap = cap, edge[e].cost = cost;
        edge[e].next = adj[x], edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].cost = -cost;
        edge[e].next = adj[y], edge[e].re = &edge[e-1], adj[y] = &edge[e++];
    }
	void Spfa() {
		memset(inq, 0, sizeof(inq[0])*n);
		memset(dist, 0x3f, sizeof(dist[0])*n);
			
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
				if (p->cap == 0 || inq[p->v])
					continue;
				if (dist[p->v] - dist[i] + p->cost < mn)
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
			if (p->cap == 0 || inq[p->v])
				continue;
			if (dist[p->v] + p->cost != dist[i])
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

int test(int x, int &ret) {
	if (x*n%m)
		return 0;
	int y = x*n/m;
	int source = n+m, sink = n+m+1;
	int ones = 0;

	g.Init(n+m+2);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '1') {
				ones++;
				g.Addedge(i, n+j, 1, -1);
			}
		}
	}	
	for (int i = 0; i < n; i++)
		g.Addedge(source, i, x, 0);
	for (int i = 0; i < m; i++)
		g.Addedge(i+n, sink, y, 0);
		
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (s[i][j] == '0')
				g.Addedge(i, n+j, 1, 1);
		}
	}
	
	if (x == 0) {
		ret = min(ret, ones);
		return 0;
	}

	static int dist[MAXV], last_cost;
	if (x == m) {
		g.st = source, g.ed = sink;
		g.Spfa();
		for (int i = 0; i <= g.n; i++)
			dist[i] = g.dist[i];
		last_cost = n*m - 2*ones;
		ret = min(ret, n*m - ones);
		return 0;
	} else {
		for (int i = 0; i <= g.n; i++)
			g.dist[i] = dist[i];
	}
	auto cost = g.Mincost(source, sink, 0);
	if (x == m) {
		last_cost = cost.first;
	} else {
		if (cost.first >= last_cost)
			return 1;
		last_cost = cost.first;
	}
//	printf("%d %d\n", cost.first, ones);
	ret = min(ret, cost.first + ones);
	return 0;
}

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while ((c = readchar()) < '-')	{ if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
inline int ReadStr(char *s) {
	static char c;
	while ((c = readchar()) <= ' ')	{if (c == EOF)	return 0;}
	*s = c, s++;
	while ((c = readchar()) > ' ')
		*s = c, s++;
	*s = '\0';
	return 1;
}

int main() {
	int testcase, cases = 0;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n), ReadInt(&m);
		for (int i = 0; i < n; i++)
//			scanf("%s", s[i]);
			ReadStr(s[i]);
				
		int ret = n*m;
		int row[64] = {}, col[64] = {}, sat = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				row[i] += s[i][j] == '1', col[j] += s[i][j] == '1';
		}
		
		for (int i = 1; i < n; i++)
			sat &= row[i] == row[0];
		for (int i = 1; i < m; i++)
			sat &= col[i] == col[0];
		if (sat) {
			ret = 0;
		} else {
			for (int i = m; i >= 0; i--) {
				if (test(i, ret))
					break;
			}
		}
		
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
