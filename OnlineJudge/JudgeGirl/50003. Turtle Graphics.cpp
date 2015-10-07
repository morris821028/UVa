#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int g[128][128] = {}, n, m;
int test(int x, int y, int p, int q) {
	if (x < 0 || y < 0 || x >= n || y >= m)	return 0;
	if (p < 0 || q < 0 || p >= n || q >= m)	return 0;
	if (x == p || y == q)			return 1;
	if (abs(x - p) == abs(y - q))	return 1;
	return 0;
}
int main() {
	int p, q;
	while (scanf("%d %d %d", &q, &n, &m) == 3) {
		int valid = 1;
		memset(g, 0, sizeof(g));
		for (int i = 0; i < q; i++) {
			int px, py, x, y, dx, dy, tx, ty;
			scanf("%d", &p);
			scanf("%d %d", &py, &px);
			for (int j = 1; j < p; j++) {
				scanf("%d %d", &y, &x);
				if (!valid)	continue;
				int f = test(x, y, px, py);
				if (!f) {
					valid = 0;
					printf("ERROR %d %d\n", i+1, j+1);
					continue;
				}
				if (x == px)	
					dx = 0, dy = py < y ? 1 : -1;
				else if (y == py)
					dy = 0, dx = px < x ? 1 : -1;
				else
					dx = px < x ? 1 : -1, dy = py < y ? 1 : -1;
				if (px != x || py != y)
				for (tx = px+dx, ty = py+dy; tx != x || ty != y; tx += dx, ty += dy)
					g[tx][ty] = 1;
				g[px][py] = g[x][y] = 1;
				px = x, py = y;
			}
		}
		if (valid) {
			for (int i = 0; i < n; i++, puts("")) {
				for (int j = 0; j < m; j++)
					printf("%d", g[n-i-1][j]);
			}
		}
	}
	return 0;
}
