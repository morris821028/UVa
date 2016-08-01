#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 65536;
vector< pair<int, int> > g[MAXN];
int f[MAXN];
long long dp[MAXN][2], sumf[MAXN];
void dfs1(int u, int p) {
	dp[u][0] = 0, sumf[u] = f[u];
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first, w = g[u][i].second;
		if (v == p)	continue;
		dfs1(v, u);
		sumf[u] += sumf[v];
		dp[u][0] += dp[v][0] + sumf[v] * w * 2;
	}
}
void dfs2(int u, int p, long long upv, long long upf) {
	dp[u][1] = upv;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i].first, w = g[u][i].second;
		if (v == p)	continue;
		long long nextv;
		nextv = upv + (upf + sumf[u] - sumf[v]) * w * 2 + (dp[u][0] - dp[v][0] - sumf[v] * w * 2);
		dfs2(v, u, nextv, upf + sumf[u] - sumf[v]);
	}
}
int main() {
	int testcase, n, m;
	int x, y, v;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)		
			f[i] = 0, g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &x, &y, &v);
			x--, y--;
			g[x].push_back(make_pair(y, v));
			g[y].push_back(make_pair(x, v));
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &v), x--;
			f[x] = v;
		}
		
		dfs1(0, -1);
		dfs2(0, -1, 0, 0);
		
		long long mn = 1LL<<60;
		vector<int> ret;
		for (int i = 0; i < n; i++)
			mn = min(mn, dp[i][0] + dp[i][1]);
		for (int i = 0; i < n; i++) {
			if (dp[i][0] + dp[i][1] == mn)
				ret.push_back(i+1);
		}
		
		printf("%lld\n", mn);
		for (int i = 0; i < ret.size(); i++)
			printf("%d%c", ret[i], i == ret.size()-1 ? '\n' : ' ');
	}
	return 0;
}
/*
2  
2  
1 2 17  
2  
1 5  
2 10  
5  
1 3 10  
2 3 20  
3 4 30  
4 5 30  
3  
1 10  
2 10  
5 20 
*/
