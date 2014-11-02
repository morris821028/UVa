#include <stdio.h> 
#include <string.h>
#include <queue>
using namespace std;

const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
int main() {
	int sx, sy, ex, ey, px, py, tx, ty;
	int cases = 0;
	while (scanf("%d %d", &sx, &sy) == 2) {
		scanf("%d %d", &ex, &ey);
		scanf("%d %d", &px, &py);
		int used[16][16] = {}, dist[16][16] = {};
		used[px][py] = 1;
		queue<int> X, Y;
		X.push(sx), Y.push(sy), used[sx][sy] = 1;
		while (!X.empty()) {
			sx = X.front(), X.pop();
			sy = Y.front(), Y.pop();
			if (sx == ex && sy == ey)	break;
			for (int i = 0; i < 8; i++) {
				tx = sx + dx[i], ty = sy + dy[i];
				if (tx <= 0 || tx > 8 || ty <= 0 || ty > 8)
					continue;
				if (used[tx][ty] == 0) {
					used[tx][ty] = 1;
					dist[tx][ty] = dist[sx][sy] + 1;
					X.push(tx), Y.push(ty);
				}
			}
		}
		printf("Case %d: %d\n", ++cases, dist[ex][ey]);
	}
	return 0;
}
