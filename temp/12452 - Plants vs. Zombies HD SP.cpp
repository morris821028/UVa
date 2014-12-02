#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 32767

vector<int> g[MAXN];
long long dp[MAXN][2]; // [node][1:protect edge from parent, 0:none]

#define INF (1LL<<50)
void dfs(int u, int p) {
	
	dp[u][0] = dp[u][1] = INF;
	
	long long cost[3] = {};
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v == p)	continue;
		dfs(v, u);
		cost[0] += dp[v][0];
		cost[1] += dp[v][1];
		cost[2] += min(dp[v][0], dp[v][1]);
	}
	dp[u][0] = min(dp[u][0], cost[1]);
	dp[u][1] = min(dp[u][1], cost[1] + 100);
	dp[u][1] = min(dp[u][1], cost[2] + 500);
	
	long long c[2] = {INF, INF};
	for (int i = 0; i < g[u].size(); i++) {// two edge with subnode and parent.
		int v = g[u][i];
		if (v == p)	continue;
		dp[u][1] = min(dp[u][1], cost[1] - dp[v][1] + dp[v][0] + 175);
		if (-dp[v][1] + dp[v][0] < c[1]) {
			c[1] = -dp[v][1] + dp[v][0];
			if (c[0] > c[1])	swap(c[0], c[1]);
		}
	}
	// two two edge with two subnodes
	dp[u][0] = min(dp[u][0], cost[1] + c[0] + c[1] + 175);
}
int main() {
	int testcase, n;
	int u, v;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(0, -1);
		printf("$%lld\n", min(dp[0][0], dp[0][1]));
	}
	return 0;
}
