#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
vector<int> g[MAXN];
int X[MAXN], Y[MAXN], C[MAXN];
int dp[MAXN];
void dfs(int u, int p) {
	dp[u] = C[u];
	for (auto &v : g[u]) {
		if (v == p)	continue;
		dfs(v, u);
		if (dp[v] > 0)
			dp[u] += dp[v];
	}
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		map< pair<int, int>, int > R;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d", &X[i], &Y[i], &C[i]);
			R[{X[i], Y[i]}] = i;
			for (int j = 0; j < 4; j++) {
				int tx = X[i] + dx[j], ty = Y[i] + dy[j];
				if (R.count({tx, ty})) {
					int u = R[{tx, ty}], v = i;
					g[u].push_back(v);
					g[v].push_back(u);
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < n; i++) {
			dfs(i, -1);
			ret = max(ret, dp[i]);
		}
		printf("%d\n", ret);
	}
	return 0;
}

/*
5
0 0 -2
0 1 1
1 0 1
0 -1 1
-1 0 1
*/ 
