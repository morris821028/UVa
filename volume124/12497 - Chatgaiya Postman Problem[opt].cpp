#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 13;
int64_t dp[2][2][MAXN][1<<MAXN];
int8_t mlog2[1<<MAXN];
int g[MAXN];
int root, n;
int64_t dfs(int u, int visited, int twice, int last) {
	if (twice && u == root)
		return 1;
	int64_t &ret = dp[twice][last][u][visited];
	if (ret != -1)
		return ret;
	int64_t tmp = 0;
	for (int i = (g[u]&~visited)|(g[u]&((1^last)<<root)); i; ) {
		int v = mlog2[i&(-i)]; i -= i&(-i);
		if (v == root) {
			tmp += dfs(v, visited, twice, 0);
		} else {
			int next_last = u == root;
			int next_twice = twice || (next_last && visited != (1<<root));
			tmp += dfs(v, visited|(1<<v), next_twice, next_last);
		}
	}
	return ret = tmp;
}
int main() {
	for (int i = 0; i < MAXN; i++)
		mlog2[1<<i] = i;
	int testcase, cases = 0;
	int m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		memset(g, 0, sizeof(g));
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u] |= 1<<v;
			g[v] |= 1<<u;
		}

		int64_t ret = 0;
		for (int i = 0; i < n; i++) {
			for (int i = 0; i < n; i++) {
				for (int p = 0; p < 2; p++)
					for (int q = 0; q < 2; q++)
						memset(dp[p][q][i], -1, sizeof(int64_t)*(1<<n));
			}
			root = i;
			ret += dfs(i, 1<<i, 0, 0);
		}
		printf("Case %d: %lld\n", ++cases, ret/8);
	}
	return 0;
}
/*
2
5  6
0  1
1  2
2  0
2  3
3  4
4  2

6  7
0  1
1  2
2  0
2  3
3  4
4  5
5  3
*/
