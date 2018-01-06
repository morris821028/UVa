#include <stdio.h>
#include <string.h>
static const int MAXS = 128;
static char g[MAXS][MAXS];
int main() {
	int testcase, n, m;
	int ret[MAXS][MAXS];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);

		for (int i = 0; i < n; i++)
			memset(ret[i], 0, sizeof(ret[0][0])*m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int cnt = 0, prev = j;
				while (j < m && g[i][j] != '#')
					cnt += g[i][j] == 'R', j++;
				while (prev < j)
					ret[i][prev] += cnt, prev++;
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int cnt = 0, prev = j;
				while (j < n && g[j][i] != '#')
					cnt += g[j][i] == 'R', j++;
				while (prev < j)
					ret[prev][i] += cnt, prev++;
			}
		}
		for (int i = 0; i < n; i++) {
			int tx = i, ty = 0;
			while (tx < n && ty < m) {
				int cnt = 0, px = tx, py = ty;
				while (tx < n && ty < m && g[tx][ty] != '#')
					cnt += g[tx][ty] == 'R', tx++, ty++;
				while (px < tx && py < ty)
					ret[px][py] += cnt, px++, py++;
				tx++, ty++;
			}
		}
		for (int i = 1; i < m; i++) {
			int tx = 0, ty = i;
			while (tx < n && ty < m) {
				int cnt = 0, px = tx, py = ty;
				while (tx < n && ty < m && g[tx][ty] != '#')
					cnt += g[tx][ty] == 'R', tx++, ty++;
				while (px < tx && py < ty)
					ret[px][py] += cnt, px++, py++;
				tx++, ty++;
			}
		}
		for (int i = 0; i < n; i++) {
			int tx = i, ty = 0;
			while (tx >= 0 && ty < m) {
				int cnt = 0, px = tx, py = ty;
				while (tx >= 0 && ty < m && g[tx][ty] != '#')
					cnt += g[tx][ty] == 'R', tx--, ty++;
				while (px > tx && py < ty)
					ret[px][py] += cnt, px--, py++;
				tx--, ty++;
			}
		}
		for (int i = 1; i < m; i++) {
			int tx = n-1, ty = i;
			while (tx >= 0 && ty < m) {
				int cnt = 0, px = tx, py = ty;
				while (tx >= 0 && ty < m && g[tx][ty] != '#')
					cnt += g[tx][ty] == 'R', tx--, ty++;
				while (px > tx && py < ty)
					ret[px][py] += cnt, px--, py++;
				tx--, ty++;
			}
		}
		
		int mx = 0, my = 0, mc = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == 'R')	ret[i][j] -= 3;
				if (ret[i][j] > mc)
					mc = ret[i][j], mx = i, my = j;
			}
		}
		printf("%d %d\n", mx+1, my+1);
	}
	return 0;
}
/*
3
5  13
..R...R..#.R.
.............
......R.R....
.R...###.....
.....RRR..R..
5  13
..R...R..#.R.
....R.....R..
......R.R...R
.R...###....R
..R..RRR.#R..
3  3
R..
###
.R.
*/
