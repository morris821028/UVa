#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
#include <assert.h>
using namespace std;

const int MAXN = 256;

struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w):
		u(u), v(v), w(w) {}
	bool operator<(const Edge &x) const {
		return w < x.w;
	}
} e[MAXN*MAXN];

struct bitGraph64 {
	uint64_t v[4];
	void reset() {
		memset(v, 0, sizeof(v[0])*4);
	}
	void fill(int n) {
		int m = n/64;
		for (int i = 0; i < m; i++)
			v[i] = ~(0ULL);
		if (n&63)
			v[m] = (1ULL<<(n&63))-1;
	}
	void flip(int x) {
		v[x>>6] ^= 1ULL<<(x&63);
	}
	int get(int x) {
		return v[x>>6]>>(x&63)&1;
	}
};
// Kosaraju + bitwise
struct SAT {
	bitGraph64 g0[MAXN<<1], g1[MAXN<<1];
	bitGraph64 v0, v1;
	bitGraph64 contract;
	int n;
	int visited[MAXN<<2];
	int findIdx;
	void init(int n) {
		this->n = n;
		for (int i = 0; i < 2*n; i++)
			g0[i].reset(), g1[i].reset();
	}
	void addEdgeA(int x, int y) {
		g0[x].flip(y);
		g0[y].flip(x);
		g1[y+n].flip(x);
		g1[x+n].flip(y);
	}
	void addEdgeB(int x, int y) {
		g0[x+n].flip(y);
		g0[y+n].flip(x);
		g1[y].flip(x);
		g1[x].flip(y);
	}
	void dfs1(int u) {
		if (u < n) {
			v0.flip(u);
			for (int i = 0; i < 4; i++) {
				for (uint64_t mask; (mask = v1.v[i] & g0[u].v[i]); )
					dfs1(((i<<6)|__builtin_ctzll(mask))+n);
			}
		} else {
			v1.flip(u-n);
			for (int i = 0; i < 4; i++) {
				for (uint64_t mask; (mask = v0.v[i] & g0[u].v[i]); )
					dfs1(((i<<6)|__builtin_ctzll(mask)));
			}
		}
		visited[findIdx++] = u;
	}
	int dfs2(int u, int p) {
		if (u < n) {
			if (contract.get(u))
				return 1;
			contract.flip(u);
			v0.flip(u);
			for (int i = 0; i < 4; i++) {
				for (uint64_t mask; (mask = v1.v[i] & g1[u].v[i]); )
					if (dfs2(((i<<6)|__builtin_ctzll(mask))+n, p))
						return 1;
			}
		} else {
			if (contract.get(u-n))
				return 1;
			contract.flip(u-n);
			v1.flip(u-n);
			for (int i = 0; i < 4; i++) {
				for (uint64_t mask; (mask = v0.v[i] & g1[u].v[i]); )
					if (dfs2(((i<<6)|__builtin_ctzll(mask)), p))
						return 1;
			}
		}
		return 0;
	}
	int solvable() {
		v0.fill(n), v1.fill(n);
		findIdx = 0;
		for (int i = 0; i < 4; i++) {
			for (int u; v0.v[i] && (u = ((i<<6)|__builtin_ctzll(v0.v[i]))) < n; )
				dfs1(u);
		}
		for (int i = 0; i < 4; i++) {
			for (int u; v1.v[i] && (u = ((i<<6)|__builtin_ctzll(v1.v[i]))) < n; )
				dfs1(u+n);
		}
		v0.fill(n), v1.fill(n);
		for (int i = findIdx-1; i >= 0; i--) {
			int u = visited[i];
			if (u < n) {
				if (v0.get(u)) {
					contract.reset();
					if (dfs2(u, u))
						return 0;
				}
			} else {
				if (v1.get(u-n)) {
					contract.reset();
					if (dfs2(u, u))
						return 0;
				}
			}
		}
		return 1;
	}
} sat;

static int parent[MAXN<<1], marke[MAXN*MAXN];
static int dist[MAXN<<1];
int findp(int x) {
	if (x == parent[x])
		return x;
	int ret = findp(parent[x]);
	dist[x] ^= dist[parent[x]];
	return parent[x] = ret;
}
int cutoff(int n, int m) {
	for (int i = 0; i < 2*n; i++)
		parent[i] = i, dist[i] = 0;
	marke[0] = 1, marke[m] = 1;
	for (int i = m-1; i >= 1; i--)
		marke[i] = 0;
	for (int i = m-1; i >= 1; i--) {
		int u = e[i].u, v = e[i].v;
		int bu = findp(u), bv = findp(v);
		if (bu != bv) {
			marke[i] = 1;
			dist[bu] = dist[u] ^ dist[v] ^ 1;
			parent[bu] = bv;
		} else if (dist[u] == dist[v]) {
			marke[i] = 1;
			break;
		}
	}
}

int group(int n, int m) {	// partition into two group
	int ret = INT_MAX;
	sort(e+1, e+m);
	sat.init(n);
	for (int i = 1; i < m; i++)
		sat.addEdgeA(e[i].u, e[i].v);
	e[0].w = 0;
	cutoff(n, m);
	for (int i = 0, j = m-1; i <= j; i++) {
		if (i)
			sat.addEdgeA(e[i].u, e[i].v);
		if (i+1 < m && e[i].w == e[i+1].w)
			continue;
		while (e[i].w + e[j].w >= ret || sat.solvable()) {
			ret = min(ret, e[i].w + e[j].w);
			if (j)
				sat.addEdgeB(e[j].u, e[j].v);
			j--;
			while (marke[j] == 0)
				j--;
			if (j < i)
				goto DONE;
		}
	}
	DONE:
	return ret;
}
int main() {
	int n;	
	while (scanf("%d", &n) == 1 && n) {
		int m = 1, w;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				scanf("%d", &w);
				e[m++] = Edge(i, j, w);
			}
		}
		
		int ret = group(n, m);
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
4 5 0 2
1 3 7
2 0
4

7
1 10 5 5 5 5
5 10 5 5 5
100 100 5 5
10 5 5
98 99
3
*/
