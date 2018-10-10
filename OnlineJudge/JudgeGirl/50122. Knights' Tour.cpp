#include <stdio.h>

int main() {
	int n, m;
	int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	static int g[105][105] = {};
	static int kx[10005], ky[10005];
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &kx[i], &ky[i]);
		g[kx[i]][ky[i]] = i*10000;
	}
	
	for (int it = 1, valid = m; valid; it++) {
		for (int i = 1; i <= m; i++) {
			if (kx[i] < 0)
				continue;
			int mn = 0x3f3f3f3f, sel = -1;
			for (int j = 0; j < 8; j++) {
				int tx = kx[i]+dx[j];
				int ty = ky[i]+dy[j];
				if (tx < 0 || tx >= n || ty < 0 || ty >= n || g[tx][ty])
					continue;
				int liberty = 0;
				for (int k = 0; k < 8; k++) {
					int px = tx+dx[k];
					int py = ty+dy[k];
					if (px < 0 || px >= n || py < 0 || py >= n || g[px][py])
						continue;
					liberty++;
				}
				if (liberty < mn)
					mn = liberty, sel = j;
			}
			if (sel == -1) {
				kx[i] = -1, valid--;
			} else {
				kx[i] += dx[sel], ky[i] += dy[sel];
				g[kx[i]][ky[i]] = i*10000 + it;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%d%c", g[i][j], " \n"[j==n-1]);
	}
	return 0;
}
