#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 100005;
const int MAXK = 105;
const int INF = 0x3f3f3f3f;
vector<int> g[MAXN];
int val[MAXN];
int dp[MAXK], n, k;
int buff[MAXK*MAXN];
void dfs(int u, int dep) {
	int *ldp = buff + dep*(k+1);
	memcpy(ldp, dp, sizeof(dp[0])*(k+1));
	for (auto v : g[u])
		dfs(v, dep+1);
	int vv = val[u];
	for (int i = 1; i <= k; i++)
		dp[i] = max(dp[i], ldp[i-1] + vv);
}
int main() {
	while (scanf("%d %d", &n, &k) == 2 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < n; i++)
			scanf("%d", &val[i]);
		for (int i = 1; i < n; i++) {
			int p;
			scanf("%d", &p);
			g[p].push_back(i);
		}
		fill(dp, dp+(k+1), -INF);
		dp[0] = 0;
		dfs(0, 0);
		int ret = -INF;
		for (int i = 1; i <= k; i++)
			ret = max(ret, dp[i]);
		printf("%d\n", ret);
	}
	return 0;
}
/*
7 3
6 3 4 -1 1 -5 1
0 1 1 0 0 5
2 1
-1 1
0
3 3
1 2 3
0 0
8 8
1 2 3 4 5 6 7 8
0 1 2 3 4 5 6
4 4
-27 -45 -67 -98
2 0 2
0 0
*/
