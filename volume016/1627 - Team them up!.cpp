#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

#define MAXN 128
int g[MAXN][MAXN], visited[MAXN];
int color[MAXN], n;
int dfs(int u, int c, vector<int> &s0, vector<int> &s1) {
	visited[u] = 1, color[u] = c;
	if (c == 0)	s0.push_back(u);
	else		s1.push_back(u);
	for (int i = 1; i <= n; i++) {
		if ((!(g[u][i] == 1 && g[i][u] == 1)) && i != u) {
			if (visited[i] == 0) {
				if (!dfs(i, !color[u], s0, s1))
					return 0;
			} else {
				if (color[u] == color[i])
					return 0;
			}
		}
	}
	return 1;
}
int main() {
	int testcase, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		while (getchar() != '\n');
		memset(g, 0, sizeof(g));
		memset(visited, 0, sizeof(visited));
		memset(color, 0, sizeof(color));
		for (int i = 1; i <= n; i++) {
			while (scanf("%d", &x) == 1 && x)
				g[i][x] = 1;
		}
		int ok = 1, m = 0;
		vector<int> s0[MAXN], s1[MAXN];
		for (int i = 1; i <= n; i++) {
			if (visited[i] == 0) {
				m++;
				ok &= dfs(i, 0, s0[m], s1[m]);
			}
		}
		if (!ok) {
			puts("No solution");
		} else {
			int dp[MAXN][MAXN] = {}, from[MAXN][MAXN] = {};
			dp[0][0] = 1;
			for (int i = 1; i <= m; i++) {
				for (int j = 0; j <= n; j++) {
					if (dp[i - 1][j]) {
						dp[i][j + s0[i].size()] = 1;
						dp[i][j + s1[i].size()] = 1;
						from[i][j + s0[i].size()] = 0;
						from[i][j + s1[i].size()] = 1;
					}
				}
			}
			int ch = -1;
			for (int i = n/2; i >= 1; i--) {
				if (dp[m][i])	ch = i, i = -1;
			}
			assert(ch > 0);
			vector<int> team1, team2;
			for (int i = m; i >= 1; i--) {
				if (from[i][ch] == 0) {
					ch -= s0[i].size();
					team1.insert(team1.end(), s0[i].begin(), s0[i].end());
					team2.insert(team2.end(), s1[i].begin(), s1[i].end());
				} else {
					ch -= s1[i].size();
					team1.insert(team1.end(), s1[i].begin(), s1[i].end());
					team2.insert(team2.end(), s0[i].begin(), s0[i].end());
				}
			}
			printf("%d", team1.size());
			for (int i = 0; i < team1.size(); i++)
				printf(" %d", team1[i]);
			puts("");
			printf("%d", team2.size());
			for (int i = 0; i < team2.size(); i++)
				printf(" %d", team2[i]);
			puts("");
		}
		if (testcase)	puts("");
	}
	return 0;
}
/*
2

5
3 4 5 0
1 3 5 0
2 1 4 5 0
2 3 5 0
1 2 3 4 0

5
2 3 5 0
1 4 5 3 0
1 2 5 0
1 2 3 0
4 3 2 1 0
*/
