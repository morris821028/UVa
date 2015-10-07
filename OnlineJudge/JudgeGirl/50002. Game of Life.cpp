#include <stdio.h>
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
int g[2][128][128] = {}, n, m;
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		int live[128][128] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &g[0][i][j]);
				if (g[0][i][j])	live[i][j]++;
			}
		}

		int p = 0, q = 1;
		for (int it = 0; it < m; it++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					int cnt = 0, tx, ty;
					for (int k = 0; k < 8; k++) {
						tx = i+dx[k], ty = j+dy[k];
						if (tx < 0 || ty < 0 || tx >= n || ty >= n)
							continue;
						cnt += g[p][tx][ty];
					}
					g[q][i][j] = g[p][i][j];
					if (g[p][i][j]) {
						if (cnt < 2 || cnt > 3)	
							g[q][i][j] = 0;
					} else {
						if (cnt == 3)	
							g[q][i][j] = 1;
					}
					if (g[q][i][j])
						live[i][j]++;
				}
			}
			p = 1 - p, q = 1 - q;
		}
		int rx = 0, ry = 0, ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d%c", g[p][i][j], " \n"[j==n-1]);
				if (live[i][j] >= ret)
					ret = live[i][j], rx = i, ry = j;
			}
		}
		printf("%d %d\n", rx+1, ry+1);
	}
	return 0;
}
