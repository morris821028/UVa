#include <bits/stdc++.h>
using namespace std;

char g[128][128][128];
int used[128][128][128];
int main() {
	int W, L, H;
	while (scanf("%d %d %d", &W, &L, &H) == 3 && W) {
		int sx, sy, sz;
		int ex, ey, ez;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%s", g[i][j]);
				for (int k = 0; k < L; k++) {
					if (g[i][j][k] == 'S') {
						sx = j, sy = k, sz = i;
					} 
					if (g[i][j][k] == 'E') {
						ex = j, ey = k, ez = i;
					}
				}
			}
		}
		
		memset(used, 0, sizeof(used));
		queue<int> X, Y, Z;
		X.push(sx);
		Y.push(sy);
		Z.push(sz);
		used[sz][sx][sy] = 1;
		const int dx[4] = {0, 0, 1, -1};
		const int dy[4] = {1, -1, 0, 0};
		const int dz[2] = {1, -1};
		while (!X.empty()) {
			sx = X.front(), X.pop();
			sy = Y.front(), Y.pop();
			sz = Z.front(), Z.pop();
			int cc = used[sz][sx][sy] + 1;
			for (int i = 0; i < 4; i++) {
				int tx, ty;
				tx = sx + dx[i];
				ty = sy + dy[i];
				if (tx < 0 || ty < 0 || tx >= W || ty >= L)
					continue;
				if (g[sz][tx][ty] == '#' || used[sz][tx][ty])
					continue;
				used[sz][tx][ty] = cc;
				X.push(tx);
				Y.push(ty);
				Z.push(sz);
			}
			if (g[sz][sx][sy] == '-') {
				for (int i = 0; i < 2; i++) {
					int tz = sz + dz[i];
					if (tz < 0 || tz >= H)
						continue;
					if (g[tz][sx][sy] != '-' || used[tz][sx][sy])
						continue;
					used[tz][sx][sy] = cc;
					X.push(sx);
					Y.push(sy);
					Z.push(tz);
				}
			}
			if (used[ez][ex][ey])
				break;
		}
		printf("%d\n", used[ez][ex][ey]-1);
	}
	return 0;
}

