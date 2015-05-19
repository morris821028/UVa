#include <stdio.h> 
#include <string.h>
#include <assert.h>
const int MAXN = 128;
int g[MAXN][MAXN], ret[MAXN][MAXN];
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int main() {
	int px, py, w, h;
	int cases = 0;
	while (scanf("%d %d %d %d", &px, &py, &w, &h) == 4) {
		assert(w < MAXN && h < MAXN);
		if (cases++)	puts("");
		
		memset(g, 0, sizeof(g));
		memset(ret, 0, sizeof(ret));
		for (int i = 0; i < MAXN; i++) {
			int x, y;
			x = px - i - 1, y = py + i + 1;
			for (int j = 0; j < 2 * (i + 1); j++) {
				if (x >= 0 && x <= w && y >= 0 && y <= h)
					g[x][y] = 1;
				y -= 1;
			}
			x = px - i, y = py + i + 1;
			for (int j = 0; j < 2 * (i + 1); j++) {
				if (x >= 0 && x <= w && y >= 0 && y <= h)
					g[x][y] = 2;
				x += 1;
			}
			x = px + i + 1, y = py + i;
			for (int j = 0; j < 2 * (i + 1); j++) {
				if (x >= 0 && x <= w && y >= 0 && y <= h)
					g[x][y] = 3;
				y -= 1;
			}
			x = px - i - 1, y = py - i - 1;
			for (int j = 0; j < 2 * (i + 1); j++) {
				if (x >= 0 && x <= w && y >= 0 && y <= h)
					g[x][y] = 4;
				x += 1;
			}
		}
		
		for (int i = h; i >= 1; i--) {
			int n, x;
			scanf("%d", &n);
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				int tx, ty;
				tx = x + dx[g[x][i] - 1];
				ty = i + dy[g[x][i] - 1];
				ret[tx][ty] = 1;
			}
		}
//		for (int i = 1; i <= w; i++, puts(""))
//			for (int j = 1; j <= h; j++)
//				printf("%d", g[i][j]);
				
		printf("%d %d %d %d\n", px, py, w, h);
		for (int i = h; i >= 1; i--) {
			int n = 0;
			for (int j = 1; j <= w; j++)
				n += ret[j][i];
			printf("%d", n);
			for (int j = 1; j <= w; j++)
				if (ret[j][i])
					printf(" %d", j);
			puts("");
		}
	}
	return 0;
}
/*
3 3 7 6
1 6
1 2
0
1 6
1 2
1 5
*/
