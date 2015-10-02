#include <stdio.h> 
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
const int dr[] = {1, 0, 3, 2};
int n, m, g[128][128];
int tolabel(int x, int y) {
	if (x == n)		return y;
	if (y == m)		return n+m-1 - x;
	if (x == -1)	return n+m+m-1 - y;
	if (y == -1)	return n+m+m + x;
	return -1;
}
int reflect(int x, int y, int dir) {
	x += dx[dir], y += dy[dir];
	while (x >= 0 && x < n && y >= 0 && y < m) {
		if (g[x][y])
			dir = dr[dir];
		x += dx[dir], y += dy[dir];
	}
	return tolabel(x, y);
}
int main() {
	while (scanf("%d %d", &m, &n) == 2) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		for (int i = 0; i < m; i++)
			printf("%d\n", reflect(n, i, 3));
		for (int i = n-1; i >= 0; i--)
			printf("%d\n", reflect(i, m, 0));
		for (int i = m-1; i >= 0; i--)
			printf("%d\n", reflect(-1, i, 1));
		for (int i = 0; i < n; i++)
			printf("%d\n", reflect(i, -1, 2));
	}
	return 0;
}

