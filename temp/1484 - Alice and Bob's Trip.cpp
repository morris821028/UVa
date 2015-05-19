#include <stdio.h> 
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 524288;
vector< pair<int, int> > g[MAXN];
int dp[MAXN][2]; // [][Bob:0, Alice:1] 
int dist2root[MAXN], dist2leaf[MAXN];
void solve(int N, int L, int R) {
	vector<int> A;
	queue<int> Q;
	int u, v, w, path;
	
	Q.push(0);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		A.push_back(u);
		for (int i = 0; i < g[u].size(); i++)
			Q.push(g[u][i].first);
	}
	
	dist2root[0] = 0;
	for (int i = 0; i < A.size(); i++) {
		u = A[i];
		for (int j = 0; j < g[u].size(); j++)
			dist2root[g[u][j].first] = dist2root[u] + g[u][j].second;
	}
	
	for (int i = A.size() - 1; i >= 0; i--) {
		u = A[i];
		
		if (g[u].size() == 0) { // leaf
			dp[u][0] = dp[u][1] = 0;
			continue;
		}
		dp[u][0] = 0;
		dp[u][1] = 0x3f3f3f3f;
			
		for (int j = 0; j < g[u].size(); j++) {
			v = g[u][j].first, w = g[u][j].second;
			path = dist2root[u] + w + dp[v][1];
			if (L <= path && path <= R)
				dp[u][0] = max(dp[u][0], w + dp[v][1]);
			path = dist2root[u] + w + dp[v][0];
			if (L <= path && path <= R)
				dp[u][1] = min(dp[u][1], w + dp[v][0]);
		}
		
//		printf("%d %d\n", dp[u][0], dp[u][1]);
	}
	if (L <= dp[0][0] && dp[0][0] <= R)
		printf("%d\n", dp[0][0]);
	else
		puts("Oh, my god!");
}
int main() {
	int N, L, R;
	int u, v, w;
	while (scanf("%d %d %d", &N, &L, &R) == 3) {
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 1; i < N; i++) {
			scanf("%d %d %d", &u, &v, &w);
			g[u].push_back(make_pair(v, w));
		}
		
		solve(N, L, R);
	}
	return 0;
}
/*
3 2 4 
0 1 1 
0 2 5 

7 2 8 
0 1 1 
0 2 1 
1 3 1 
1 4 10 
2 5 1 
2 6 5

7 4 8 
0 1 1 
0 2 1 
1 3 1 
1 4 2 
2 5 1 
2 6 5
 
4 2 6 
0 1 1 
1 2 1 
1 3 5
*/
