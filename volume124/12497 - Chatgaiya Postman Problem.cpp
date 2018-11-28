#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 13;
int64_t dp[2][2][MAXN][1<<MAXN];
int g[MAXN][MAXN];
int root, n;
int64_t dfs(int u, int visited, int twice, int last) {
	if (twice && u == root)
		return 1;
	int64_t &ret = dp[twice][last][u][visited];
	if (ret != -1)
		return ret;
	int64_t tmp = 0;
	for (int i = 0; i < n; i++) {
		if (!g[u][i])
			continue;
		if (i == root) {
			if (last)
				continue;
			tmp += dfs(i, visited, twice, 0);
		} else {
			if ((visited>>i)&1)
				continue;
			int next_last = u == root;
			int next_twice = twice || (next_last && visited != (1<<root));
			tmp += dfs(i, visited|(1<<i), next_twice, next_last);
		}
	}
	return ret = tmp;
}
int main() {
	int testcase, cases = 0;
	int m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		memset(g, 0, sizeof(g));
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u][v] = g[v][u] = 1;
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
