#include <stdio.h>

int g[9][9], ret[9][9] = {};
const int dx[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {0, -1, 1, 0, 1, -1, 0, 1, -1};
#define isValid(x, y) (x >= 0 && x < 9 && y >= 0 && y < 9)
int canplace(int x, int y) {
	static int tx, ty;
	for (int i = 0; i < 9; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (isValid(tx, ty) && g[tx][ty] == 0) {
			return 0;
		}
	}
	return 1;
}
int _remove(int x, int y) {
	ret[x][y] = 1;
	static int tx, ty;
	for (int i = 0; i < 9; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (isValid(tx, ty))
			g[tx][ty]--;
	}
}
int _resume(int x, int y) {
	static int tx, ty;
	for (int i = 0; i < 9; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (isValid(tx, ty))
			g[tx][ty]++;
	}
	ret[x][y] = 0;
}
int safe(int x, int y) {
	if (!isValid(x, y))	return 1;
	return g[x][y] == 0;
}
int dfs(int x, int y) {
	if (y == 9) {
		if (!safe(x-1, y-1) || !safe(x-1, y-2))
			return 0;
		x++, y = 0;
	}
	if (x == 9) {
		for (int i = 0; i < 9; i++)
			if (!safe(8, i))
				return 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				printf("%d%c", ret[i][j], j == 8 ? '\n' : ' ');
		return 1;
	}
	if (!safe(x-1, y-2))
		return 0;
	if (dfs(x, y+1))
		return 1;
	int f = canplace(x, y);
	if (f) {
		_remove(x, y);
		if (dfs(x, y+1))
			return 1;
		_resume(x, y);
	}
	return 0;
}
int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			scanf("%d", &g[i][j]);
	}
	int t = dfs(0, 0);
	if (!t)	puts("no solution");
	return 0;
}
