#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
vector<int> g[MAXN];
const int64_t MOD = 1000000007; 
int pow2[MAXN], rpow2[MAXN];
int stamp = 0;
struct footprint {
	int l, r, h, leaf;
} f[MAXN];
int64_t mpow(int64_t x, int64_t y, int64_t mod) {
	int64_t ret = 1;
	while (y) {
		if (y&1)
			ret = (ret*x)%mod;
		y >>= 1, x = (x*x)%mod;
	}
	return ret;
}
void dfs(int u, int p, int dep) {
	stamp++;
	f[u].l = stamp, f[u].h = dep;
	int ch = 0;
	for (auto v : g[u]) {
		if (v == p)
			continue;
		dfs(v, u, dep+1);
		ch = 1;
	}
	f[u].r = stamp;
	f[u].leaf = ch == 0;
}
void init() {
	pow2[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pow2[i] = pow2[i-1]<<1;
		if (pow2[i] >= MOD)
			pow2[i] -= MOD;
	}
	int64_t inv2 = mpow(2, MOD-2, MOD);
	rpow2[0] = 1, rpow2[1] = inv2;
	for (int i = 2; i < MAXN; i++)
		rpow2[i] = (rpow2[i-1] * inv2)%MOD;
}
int tree[MAXN];
void add(int x, int n, int v) {
	while (x <= n) {
		tree[x] += v;
		if (tree[x] >= MOD)
			tree[x] -= MOD;
		x += x&(-x);
	}
}
int sum(int x) {
	int64_t ret = 0;
	while (x) {
		ret += tree[x];
		x -= x&(-x);
	}
	return ret%MOD;
}
int main() {
	init();
	int testcase, cases = 0;
	int n, q;
	scanf("%d", &testcase);
	while (testcase--) {
		assert(scanf("%d", &n) == 1);
		for (int i = 0; i < n; i++)
			g[i].clear();
		int cmd, u, v, x, y;
		for (int i = 1; i < n; i++) {
			assert(scanf("%d %d", &x, &y) == 2);
			x--, y--;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		memset(tree, 0, sizeof(tree[0])*(n+1));
		stamp = 0;
		dfs(0, -1, 0);
		scanf("%d", &q);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d", &u), u--;
				int64_t s = sum(f[u].r) - sum(f[u].l-1);
				s = (s%MOD + MOD)%MOD;
//				printf("---- %lld %d\n", s, f[u].h);
				if (f[u].leaf)
					s = (s * rpow2[f[u].h])%MOD;
				else
					s = (s * rpow2[f[u].h+1])%MOD;
				printf("%lld\n", s);
			} else {
				scanf("%d %d", &u, &v), u--;
				add(f[u].l, n, ((int64_t) v*pow2[f[u].h])%MOD);
			}
		}
	}
	return 0;
}
/*
1
4
1 2
1 3
3 4
6
2 2 1
1 1
1 3
2 4 3
1 1
1 3
*/ 
