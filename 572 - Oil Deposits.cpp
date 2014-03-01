#include <stdio.h>
#include <stdlib.h>
int main() {
	int n, m, i, j, k, l;
	char map[101][101];
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0)
			break;
		for(i = 0; i < n; i++)
			scanf("%s", &map[i]);
		int ans = 0, x, y, tx, ty;
		int Dx[8] = {0, 0,1, 1,1,-1,-1,-1};
		int Dy[8] = {1,-1,0,-1,1,0,-1,1};
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++) {
				if(map[i][j] == '@') {
					ans++;
					int Q[10000][2], Qidx = 0;
					Q[0][0] = i, Q[0][1] = j;
					map[i][j] = '*';
					for(k = 0; k <= Qidx; k++) {
						x = Q[k][0], y = Q[k][1];
						for(l = 0; l < 8; l++) {
							tx = x + Dx[l], ty = y + Dy[l];
							if(tx >= 0 && tx < n && ty >= 0 && ty < m) {
								if(map[tx][ty] == '@') {
									Qidx++; 
									Q[Qidx][0] = tx;
									Q[Qidx][1] = ty;
									map[tx][ty] = '*';
								}
							}
						}
					}
				}
			}
		}
		printf("%d\n", ans);
	}
    return 0;
}
