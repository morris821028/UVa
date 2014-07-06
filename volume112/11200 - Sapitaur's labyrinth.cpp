#include <stdio.h> 
#include <string.h>
char g[512][512];
int ret = 0, n, m;
const int dx[] = {1, 0, -1, 0}; // N, E, S, W
const int dy[] = {0, 1, 0, -1};
void dfs(int x, int y, int fdir) {
	if(x == n)	ret++;
	if(x < 0 || y < 0 || x >= n || y >= m)
		return;
	int dir = 0;
	if(g[x][y] == '\\') {
		switch(fdir) {
			case 0: dir = 1; break;
			case 1: dir = 0; break;
			case 2: dir = 3; break;
			case 3: dir = 2; break;
		}
	} else {
		switch(fdir) {
			case 0: dir = 3; break;
			case 3: dir = 0; break;
			case 1: dir = 2; break;
			case 2: dir = 1; break;
		}
	}
	dfs(x + dx[dir], y + dy[dir], dir);
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &m, &n);
		for(int i = 0; i < n; i++)
			scanf("%s", g[i]);
			
		ret = 0;
		for(int i = 0; i < m; i++)
			dfs(0, i, 0);
		printf("%d\n", ret);
	}
	return 0;
}
