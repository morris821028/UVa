#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

static char g[512][512];
static const int dx[8] = {0, 1, 0, -1, 0, 1};
static const int dy[8] = {0, 0, 1, 0, -1, 1};
static int fx, fy;
int vfind(int x, int l, int r) {
	int ret = 0;
	for (int i = l; i <= r && ret < 2; i++) {
		if (g[i][x] == '2')
			ret++, fy = i, fx = x;
	}
	return ret;
}
int hfind(int x, int l, int r) {
	int ret = 0;
	for (int i = l; i <= r && ret < 2; i++) {
		if (g[x][i] == '2')
			ret++, fy = x, fx = i;
	}
	return ret;
}
int main() {
	int N, M, L, W, O;
	while (scanf("%d %d %d %d", &N, &M, &L, &W) == 4) {
		scanf("%d", &O);
		memset(g, '0', sizeof(g));
		for (int i = 0; i < O; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			g[y][x] = '2';
		}
		
		int lx = 0, ly = 0, cmd;
		while (scanf("%d", &cmd) == 1) {
			int tx, ty, rx, ry;
			rx = lx+W-1, ry = ly+L-1;
			if (cmd == 0) {
				for (int i = 0; i < N; i++) {
					static char out[512];
					out[M] = '\0';
					for (int j = 0; j < M; j++) {
						if (ly <= i && i <= ry && lx <= j && j <= rx)
							out[j] = '1';
						else
							out[j] = g[i][j];
					}
					puts(out);
				}
				continue;
			}
			tx = lx+dx[cmd], ty = ly+dy[cmd];
			if (tx < 0 || ty < 0 || tx+W > M || ty+L > N)
				continue;
			
			int ob = 0;
			if (cmd == 1)
				ob = vfind(rx+1, ly, ry);
			else if (cmd == 2)
				ob = hfind(ry+1, lx, rx);
			else if (cmd == 3)
				ob = vfind(lx-1, ly, ry);
			else if (cmd == 4)
				ob = hfind(ly-1, lx, rx);
			else if (cmd == 5) {
				ob = vfind(rx+1, ly+1, ry+1);
				if (ob <= 1) 
					ob += hfind(ry+1, lx+1, rx);
			}
				
			if (ob > 1)
				continue;
			if (ob == 1)
				g[fy][fx] = '0';
			lx = tx, ly = ty;
		}
	}
	return 0;
}
