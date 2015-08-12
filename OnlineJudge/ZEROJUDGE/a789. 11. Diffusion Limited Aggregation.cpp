#include <bits/stdc++.h>
using namespace std;

int g[16][16];
char ret[16][16] = {};
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
void dfs(int x, int y) {
	if (ret[x][y] == '*')	
		return ;
	ret[x][y] = '*';
	int tx, ty, ox = -1, oy = -1;
	for (int i = 0; i < 8; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= 11 || ty >= 11)
			continue;
		if (g[tx][ty] < g[x][y] && (ox == -1 || g[tx][ty] < g[ox][oy]))
			ox = tx, oy = ty;			
	}
	if (ox != -1)
	for (int i = 0; i < 8; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= 11 || ty >= 11)
			continue;
		if (g[tx][ty] == g[ox][oy])
			dfs(tx, ty);
	}
}
int main() {
	while (true) {
		memset(ret, '.', sizeof(ret));
		for (int i = 0; i < 11; i++)
			for (int j = 0; j < 11; j++)
				if (scanf("%d", &g[i][j]) != 1)
					return 0;
		int x, y;
		while (scanf("%d %d", &x, &y) == 2 && x >= 0)
			dfs(y, x);
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++)
				putchar(ret[i][j]);
			puts("");
		}
	}
	return 0;
}
