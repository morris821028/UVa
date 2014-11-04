#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector< pair<int, int> > g[1024];
void bfs(int u, int A[], int An, int rg[][128]) {
	int t;
	queue<int> Q, T;
	Q.push(u), T.push(0);
	rg[u][0] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		t = T.front(), T.pop();
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first;
			if (t < An && g[u][i].second == A[t]) {
				if (rg[v][t+1] == 0)  {
					rg[v][t+1] = 1;
					Q.push(v), T.push(t+1);
				}
			}
		}
	}
}
int main() {
	int n, m, t, cases = 0;
	int x, y, z, A[128]; 
	int g1[128][128], g2[128][128];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &z);
			g[x].push_back(make_pair(y, z));
			g[y].push_back(make_pair(x, z));
		}
		scanf("%d", &t);
		for (int i = 0; i < t; i++)
			scanf("%d", &A[i]);
		
		memset(g1, 0, sizeof(g1));
		memset(g2, 0, sizeof(g2));
		bfs(0, A, t, g1);
		reverse(A, A+t);
		bfs(n-1, A, t, g2);
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int ok = 0;
			for (int j = 0; j <= t; j++)
				ok |= g1[i][j] && g2[i][t - j];
			ret += ok;
		}
		printf("Tour %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3 2
0 1 1
0 2 2
3
1 1 2
3 2
0 1 1
0 2 2
1
1
0 0
*/
