#include <bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXE = MAXN<<1;
struct Edge {
	int to, d, l;
	Edge *next;
	Edge(int to=0, int d=0, int l=0, Edge *next=NULL):
		to(to), d(d), l(l), next(next) {}
};
Edge edge[MAXE], *adj[MAXN];
int e = 0;
void addEdge(int x, int y, int d, int l)  {
    edge[e] = Edge(y, d, l, adj[x]), adj[x] = &edge[e++];
    edge[e] = Edge(x, d, l, adj[y]), adj[y] = &edge[e++];
}
int32_t ret = 0;
void dfs(int u, int p, int m, map<int32_t, int32_t> &S1) {
	for (Edge *edge = adj[u]; edge; edge = edge->next) {
		Edge e = *edge;
		if (e.to == p)
			continue;
		map<int32_t, int32_t> S2;
		// <damage, length>: maintain upper convex curve
		dfs(e.to, u, m, S2);
		S2.insert({0, 0});
		for (auto it = S2.begin(); it != S2.end(); it++) {
			if (it->first + e.d <= m) {
				ret = max(ret, it->second + e.l);
			} else {
				S2.erase(it, S2.end());
				break;
			}
		}
		// merge solution from upper convex curve
		auto qt = S1.end(); 
		for (auto it : S2) {
			while (qt == S1.end() || qt->first > m - (it.first + e.d)) {
				if (qt == S1.begin())
					goto UPDATE;
				qt--;
			}
			if (qt->first + it.first + e.d <= m)
				ret = max(ret, it.second + e.l + qt->second);
		}
		// combine two convex curve into one
		UPDATE:
		auto pt = S1.lower_bound(S2.begin()->first + e.d);
		for (auto it : S2) {
			int len = it.second + e.l;
			while (pt != S1.end() && pt->first < it.first + e.d)
				pt++;
			if (pt != S1.begin()) {
				auto qt = pt; qt--;
				if (qt->second >= len)
					continue;
			}
			while (pt != S1.end() && pt->second <= len)
				pt = S1.erase(pt);
			if (pt != S1.end() && pt->first == it.first + e.d)
				continue;
			pt = S1.insert(pt, {it.first + e.d, it.second + e.l});
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
	int testcase, cases = 0;
	int n, m;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n); ReadInt(&m);
//		for (int i = 0; i < n; i++)
//			g[i].clear();
		e = 0;
		memset(adj, 0, sizeof(adj[0])*n);
		for (int i = 1; i < n; i++) {
			int u, v, d, l;
//			scanf("%d %d %d %d", &u, &v, &d, &l);
			ReadInt(&u); ReadInt(&v); ReadInt(&d); ReadInt(&l);
			u--, v--;
			addEdge(u, v, d, l);
		}
		ret = 0;
		map<int32_t, int32_t> buf;
		dfs(0, -1, m, buf);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
4  2
1  2  1  1
1  3  1  2
1  4  2  3
4  3
1  2  1  1
1  3  1  2
1  4  2  3

1
10 20
1 2 5 8
1 3 9 4
1 4 3 8
2 5 9 5
3 6 2 9
3 7 2 5
2 8 2 4
3 9 8 7
7 10 7 10

8 - 2 - 1 - 3 - 6
(2 8 2 4) + (1 2 5 8) + (1 3 9 4) + (3 6 2 9) => (18, 25)

1
10 20
1 2 7 4
2 3 6 4
2 4 9 2
1 5 2 5
4 6 7 8
5 7 9 5
6 8 3 10
1 9 8 5
7 10 3 10

1
10 20
1 2 7 4
2 3 10 3
1 4 9 10
1 5 8 4
2 6 6 3
5 7 10 10
2 8 7 9
5 9 9 8
8 10 8 1
*/
