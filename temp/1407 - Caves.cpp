// tree dp, 0/1 knapsack
#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 512;
const int INF = 0x3f3f3f3f;
struct Edge {
	int to, v;
	Edge(int a = 0, int b = 0):
		to(a), v(b) {}
};
vector<Edge> g[MAXN];
int visited[MAXN], sz[MAXN];
int dp[MAXN][MAXN][2]; // dp[i-node as root][pass j-node][back to root, or not]

int dfs(int u, int p) {
	visited[u] = 1;
	sz[u] = 1;
	int v, w;
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i].to;
		if (visited[v] || v == p)
			continue;
		sz[u] += dfs(v, u);
	}
	
	dp[u][1][0] = dp[u][1][1] = 0;
	for (int i = 0; i < g[u].size(); i++) {
		v = g[u][i].to, w = g[u][i].v;
		if (v == p)	continue;
		for (int j = sz[u]; j >= 1; j--) {
			for (int k = 1; k <= sz[v] && j - k > 0; k++) {
				int c1 = dp[u][j-k][1] + dp[v][k][0] + w;
				int c2 = dp[u][j-k][0] + dp[v][k][1] + 2 * w;
				int c3 = dp[u][j-k][1] + dp[v][k][1] + 2 * w;
				dp[u][j][0] = min(dp[u][j][0], min(c1, c2));
				dp[u][j][1] = min(dp[u][j][1], c3);
			}
		}
	}
	return sz[u];
}
int main() {
	int n, m, cases = 0;
	int x, y, v;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
			
		int in[MAXN] = {};
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &x, &y, &v);
			g[y].push_back(Edge(x, v));
			in[x]++;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= n; j++)
				dp[i][j][0] = dp[i][j][1] = INF;
		}
		
		int root = -1;
		for (int i = 0; i < n; i++)
			if (in[i] == 0)
				root = i;
				
		memset(visited, 0, sizeof(visited));
		dfs(root, -1);
		
		vector< pair<int, int> > A;
		for (int i = 1; i <= n; i++) {
			int c = min(dp[root][i][0], dp[root][i][1]);
			A.push_back(pair<int, int>(c, i));
		}
		sort(A.begin(), A.end());
		for (int i = 0, j = 0; i < A.size(); i++) {
			j = max(j, A[i].second);
			A[i].second = j;
		}
		
		printf("Case %d:\n", ++cases);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			int pos = (int) (upper_bound(A.begin(), A.end(), pair<int, int>(x, INF)) - A.begin());
			if (pos == 0)
				printf("0\n");
			else
				printf("%d\n", A[pos-1].second);
		}		
	}
	return 0;
}
/*
3 
1 0 5 
2 0 3 
4
-1
3 
10 
11 
0
*/
