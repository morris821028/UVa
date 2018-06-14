#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

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
		memset(v, 0, sizeof(v));
	}
	void fill(int n) {
		int m = n/64;
		for (int i = 0; i < m; i++)
			v[i] = ~0ULL;
		if (n&63)
			v[m] = (1ULL<<(n&63))-1;
	}
	inline void flip(int x) {
		v[x>>6] ^= 1ULL<<(x&63);
	}
	inline int get(int x) {
		return v[x>>6]>>(x&63)&1;
	}
};
struct SAT {
	bitGraph64 g0[MAXN<<1], g1[MAXN<<1];
	bitGraph64 v0, v1;
	int n;
	int visited[MAXN<<1], contract[MAXN<<1];
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
		int64_t mask;
		if (u < n) {
			v0.flip(u);
			for (int i = 0; i < 4; i++) {
				while ((mask = v1.v[i] & g0[u].v[i]))
					dfs1(((i<<6)|__builtin_ctzll(mask))+n);
			}
		} else {
			v1.flip(u-n);
			for (int i = 0; i < 4; i++) {
				while ((mask = v0.v[i] & g0[u].v[i]))
					dfs1(((i<<6)|__builtin_ctzll(mask)));
			}
		}
		visited[findIdx++] = u;
	}
	void dfs2(int u, int p) {
		int64_t mask;
		contract[u] = p;
		if (u < n) {
			v0.flip(u);
			for (int i = 0; i < 4; i++) {
				while ((mask = v1.v[i] & g1[u].v[i]))
					dfs2(((i<<6)|__builtin_ctzll(mask))+n, p);
			}
		} else {
			v1.flip(u-n);
			for (int i = 0; i < 4; i++) {
				while ((mask = v0.v[i] & g1[u].v[i]))
					dfs2(((i<<6)|__builtin_ctzll(mask)), p);
			}
		}
	}
	int solvable() {
		uint64_t mask;
		v0.fill(n), v1.fill(n);
		findIdx = 0;
		for (int i = 0; i < 4; i++) {
			while (mask = v0.v[i])
				dfs1(((i<<6)|__builtin_ctzll(mask)));
		}
		for (int i = 0; i < 4; i++) {
			while (mask = v1.v[i])
				dfs1(((i<<6)|__builtin_ctzll(mask))+n);
		}
		v0.fill(n), v1.fill(n);
		for (int i = findIdx-1; i >= 0; i--) {
			int u = visited[i];
			if (u < n) {
				if (v0.get(u))
					dfs2(u, u);
			} else {
				if (v1.get(u-n))
					dfs2(u, u);
			}
		}
		for (int i = 0; i < n; i++) {
			if (contract[i] == contract[i+n])
				return 0;
		}
		return 1;
	}
} sat;

int group(int n, int m) {	// partition into two group
	int ret = INT_MAX;
	sort(e+1, e+m);
	sat.init(n);
	for (int i = 1; i < m; i++)
		sat.addEdgeA(e[i].u, e[i].v);
	for (int i = 0, j = m-1; i <= j; i++) {
		if (i)
			sat.addEdgeA(e[i].u, e[i].v);
		while (e[i].w + e[j].w >= ret || sat.solvable()) {
			ret = min(ret, e[i].w + e[j].w);
			if (j)
				sat.addEdgeB(e[j].u, e[j].v);
			j--;
			if (j < i)
				return ret;
		}
	}
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
