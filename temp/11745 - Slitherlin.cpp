#include <stdio.h> 
#include <string.h>
char g[256][256];
int visited[256][526];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int n, m, loop, loops;
void dfs(int x, int y, int px, int py, int sx, int sy, int loopSize) {
	visited[x][y] = 1;
	int tx, ty;
//	printf("%d %d\n", x, y);
	for (int i = 0; i < 4; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx > 2 * n + 1 || ty > 2 * m + 1)
			continue;
		if (g[tx][ty] == '-') {
			ty += dy[i];
			if (tx == px && ty == py)	continue;
			if (tx == sx && ty == sy)
				loop = 1, loops = loopSize + 1;
			if (visited[tx][ty] == 0)
				dfs(tx, ty, x, y,sx, sy, loopSize+1);
		} else if (g[tx][ty] == '|') {
			tx += dx[i];
			if (tx == px && ty == py)	continue;
			if (tx == sx && ty == sy)
				loop = 1, loops = loopSize + 1;
			if (visited[tx][ty] == 0)
				dfs(tx, ty, x, y, sx, sy, loopSize+1);
		}
		if (loop)	return;
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		while(getchar() != '\n');
		for (int i = 0; i < 2 * n + 1; i++)
			gets(g[i]);
		
		int sum = 0, ok = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int x = i * 2 + 1, y = 2 * j + 1, tx, ty;
				if (g[x][y] == ' ')	continue;
				int e = g[x][y] - '0', cnt = 0;
				sum += e;
				for (int k = 0; k < 4; k++) {
					tx = x + dx[k], ty = y + dy[k];
					if (g[tx][ty] == '-' || g[tx][ty] == '|')
						cnt++;
				}
				ok &= e == cnt;
			}
		}
		memset(visited, 0, sizeof(visited));
		loop = 0;
		for (int i = 0; i < 2 * n + 1; i++) {
			for (int j = 0; j < 2 * m + 1; j++) {
				if (g[i][j] == '-') {
					dfs(i, j-1, -1, -1, i, j-1, 0);
					i = 2 * n + 1, j = 2 * m + 1;
				}
				if (g[i][j] == '|') {
					dfs(i-1, j, -1, -1, i-1, j, 0);
					i = 2 * n + 1, j = 2 * m + 1;
				}
			}
		}
		int road = 0;
		for (int i = 0; i < 2 * n + 1; i++)
			for (int j = 0; j < 2 * m + 1; j++)
				road += g[i][j] == '-' || g[i][j] == '|';
		ok &= loop == 1 && road == loops;
//		printf("%d %d %d\n", loop, loops, road);
		puts(ok ? "Valid" : "Invalid");
	}
	return 0;
}
