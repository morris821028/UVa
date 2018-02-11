#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 16;
vector<pair<int, int>> g[MAXN];
double dp[1<<MAXN][MAXN];
char ej[1<<MAXN][MAXN];
int n, m;
int run(int mask, int u) {
	if (mask == 0)
		return ej[mask][u] = 1;
	char &ret = ej[mask][u];
	if (ret != -1)	
		return ret;
	ret = 0;
	for (auto e : g[u]) {
		int v = e.first;
		if ((mask>>v)&1) {
			ret |= run(mask^(1<<v), v);
			if (ret)
				break;
		}
	}
	return ret;
}
double dfs(int mask, int u) {
	if (mask == 0)
		return 0;
	double &ret = dp[mask][u];
	if (ret != -1)
		return ret;
	ret = 0;
	double a = 0, b = 0;
	for (auto e : g[u]) {
		int v = e.first, w = e.second;
		if ((mask>>v)&1) {
			if (run(mask^(1<<v), v)) {
				b++;
				a += w + dfs(mask^(1<<v), v);
			}
		}
	}
	if (b)
		ret = (5 + a) / b;
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back({y, w});
			g[y].push_back({x, w});
		}
		for (int i = 0; i < n; i++)
			sort(g[i].begin(), g[i].end());
		for (int i = 0; i < (1<<n); i++) {
			fill(dp[i], dp[i]+MAXN, -1);
			fill(ej[i], ej[i]+MAXN, -1);
		}
		double ret = dfs(((1<<n)-1)-1, 0);
		printf("Case %d: %.10lf\n", ++cases, ret);
	}
	return 0;
}
/*
3

3 2
0 1 3
1 2 3

4 6
0 1 75
0 2 86
0 3 4
1 2 1
1 3 53
2 3 10

5 5
0 1 10
1 2 20
2 3 30
1 3 20
3 4 10
*/
