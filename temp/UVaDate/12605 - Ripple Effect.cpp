#include <stdio.h> 
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int MAXN = 32;
char s[MAXN][MAXN];
int n, m, g[MAXN][MAXN], used[MAXN][MAXN];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
const int dm[] = {1, 2, 4, 8};
void dfs(int x, int y, vector<int> &c) {
	used[x][y] = 1;
	c.push_back(s[x][y] - '0');
	int tx, ty;
	for (int i = 0; i < 4; i++) {
		if (g[x][y]&dm[i]) {
			tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if (used[tx][ty] == 0)
				dfs(tx, ty, c);
		}
	}
}
int test() {
	memset(used, 0, sizeof(used));
	for (int i = 0; i < n; i++) {
		for (int j = 0 ; j < m; j++)  {
			if (used[i][j] == 0) {
				vector<int> c;
				dfs(i, j, c);
				sort(c.begin(), c.end());
				for (int k = 0; k < c.size(); k++) {
//					printf("%d ", c[k]);
					if (c[k] != k+1)
						return 0;
				}
//				puts("");
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				if (k == j)	continue;
				if (s[i][j] == s[i][k] && abs(k-j) <= s[i][j] - '0')
					return 0;
			}
			for (int k = 0; k < n; k++) {
				if (k == i)	continue;
				if (s[i][j] == s[k][j] && abs(k-i) <= s[k][j] - '0')
					return 0;
			}
		}
	}
	return 1;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		
		int f = test();
		puts(f ? "valid" : "invalid");
	}
	return 0;
}
/*
2
6 6
241321
312432
131243
423121
214312
141231
2 12 4 4 6 8
4 5 1 5 5 4
5 1 0 5 1 5
3 8 4 1 4 1
2 10 9 2 9 4
0 2 10 10 8 1
6 6
421321
312432
131243
423121
214312
141231
2 12 4 4 6 8
4 5 1 5 5 4
5 1 0 5 1 5
3 8 4 1 4 1
2 10 9 2 9 4
0 2 10 10 8 1
*/
