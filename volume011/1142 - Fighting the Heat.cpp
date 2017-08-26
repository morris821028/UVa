#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, w;
	char dic[256][64], g[64][64];
	while (scanf("%d %d", &n, &m) == 2) {
		scanf("%d", &w);
		for (int i = 0; i < w; i++)
			scanf("%s", &dic[i]);
		
		for (int i = 0; i < n; i++)
			scanf("%s", &g[i]);
			
		int used[64][64] = {};
		const int dx[] = {0, 0, -1, -1, -1, 1, 1, 1};
		const int dy[] = {1, -1, 1, 0, -1, 1, 0, -1};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < w; k++) {
					for (int d = 0; d < 8; d++) {
						int valid = 1;
						int tx = i, ty = j, idx = 0;
						while (dic[k][idx]) {
							if (tx >= n || ty >= m || tx < 0 || ty < 0) {
								valid = 0;
								break;
							}
							if (g[tx][ty] != dic[k][idx]) {
								valid = 0;
								break;
							}
							idx++, tx += dx[d], ty += dy[d];
						}
						
						if (dic[k][idx])
							valid = 0;
						if (valid) {
							tx = i, ty = j, idx = 0;
							while (dic[k][idx]) {
								used[tx][ty] = 1;
								idx++, tx += dx[d], ty += dy[d];	
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				if (used[i][j] == 0)
					putchar(g[i][j]);
		}
		puts("");
	}
	return 0;
}
/*
6 6
7
ALLY
BARE
BARED
FINES
HIND
LORD
WONG
BBARED
ACALHF
RWOEII
EROSNN
DARNDE
ALLYGS
*/
