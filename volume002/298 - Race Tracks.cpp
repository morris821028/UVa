#include <stdio.h> 
#include <queue>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;
int g[64][64];
int testcase, N, M, P;
int sx, sy, ex, ey;
void bfs() {
	int dp[64][64][8][8] = {};
	queue<int> X, Y, VX, VY;
	int x, y, vx, vy, tx, ty, dx, dy;
	dp[sx][sy][0+3][0+3] = 1;
	X.push(sx), Y.push(sy), VX.push(0), VY.push(0);
	while(!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		vx = VX.front(), VX.pop();
		vy = VY.front(), VY.pop();
		if(x == ex && y == ey) {
			printf("Optimal solution takes %d hops.\n", dp[x][y][vx+3][vy+3]-1);
			return;
		}
		for(int i = -1; i <= 1; i++) {
			for(int j = -1; j <= 1; j++) {
				dx = vx + i, dy = vy + j;
				if(abs(dx) <= 3 && abs(dy) <= 3) {
					tx = x + dx, ty = y + dy;
					if(tx < 0 || tx >= N || ty < 0 || ty >= M || dp[tx][ty][dx+3][dy+3])
						continue;
					if(g[tx][ty])
						continue;
					dp[tx][ty][dx+3][dy+3] = dp[x][y][vx+3][vy+3] + 1;
					X.push(tx), Y.push(ty);
					VX.push(dx), VY.push(dy);
				} 
			}
		}
	}
	puts("No solution.");
}
int main() {
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		scanf("%d", &P);
		memset(g, 0, sizeof(g));
		for(int i = 0; i < P; i++) {
			int lx, ly, rx, ry;
			scanf("%d %d %d %d", &lx, &rx, &ly, &ry);
			for(int p = lx; p <= rx; p++)
				for(int q = ly; q <= ry; q++)
					g[p][q] = 1;
		}
		bfs();
	}
	return 0;
}
