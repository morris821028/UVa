#include <bits/stdc++.h> 
using namespace std;

const int MAXW = 20;
static char g[10000][MAXW+1];

int main() {
	int w, h;
	int p[4];
	int testcase = 0;
	while (scanf("%d %d", &w, &h) == 2) {
		scanf("%d %d %d %d", &p[0], &p[1], &p[2], &p[3]);
		for (int i = 0; i < h; i++)
			scanf("%s", g[i]);

		int enter = 0;
		for (int i = 0; i < w; i++) {
			if (g[0][i] == '.')
				enter++;
		}
		
		static double f[10000][MAXW][MAXW*3+1];
		memset(f, 0, sizeof(f));
		
		for (int y = 0; y < w; y++) {
			if (g[0][y] == '.')
				f[0][y][60] = 1.0/enter;
		}
		
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (g[i][j] != '.')
					continue;
				f[i][j][20+j] = 1.0;
				int tot = 0;
				if (j > 0 && g[i][j-1] != 'X')
					tot += p[2];
				if (j+1 < w && g[i][j+1] != 'X')
					tot += p[3];
				if (i > 0 && g[i-1][j] != 'X')
					tot += p[0];
				if (i+1 < h && g[i+1][j] != 'X')
					tot += p[1];
				if (tot == 0)
					continue;
				if (j > 0 && g[i][j-1] != 'X')
					f[i][j-1][20+j] -= (double) p[2] / tot;
				if (j+1 < w && g[i][j+1] != 'X')
					f[i][j+1][20+j] -= (double) p[3] / tot;
				if (i > 0 && g[i-1][j] != 'X')
					f[i-1][j][40+j] -= (double) p[0] / tot;
				if (i+1 < h && g[i+1][j] != 'X')
					f[i+1][j][j] -= (double) p[1] / tot;
			}
		}
		
		for (int x = 0; x < h; x++) {
			for (int y = 0; y < w; y++) {
				double c = f[x][y][20+y];
				if (c == 0)
					continue;
				c = 1.0/c;
				for (int i = 20+y; i < 61; i++)
					f[x][y][i] *= c;
				for (int y2 = y+1; y2 < w; y2++) {
					const double c = f[x][y2][20+y];
					if (c == 0)
						continue;
					for (int i = 20+y; i < 61; i++)
						f[x][y2][i] -= c * f[x][y][i];
				}
				
				if (x+1 < h) {
					for (int y2 = 0; y2 < w; y2++) {
						const double c = f[x+1][y2][y];
						if (c == 0)
							continue;
						for (int i = 20+y; i < 60; i++)
							f[x+1][y2][i-20] -= c * f[x][y][i];
						f[x+1][y2][60] -= c * f[x][y][60];
					}
				}
			}
		}
		
		static double val[10000][MAXW];
				
		for (int x = h-1; x >= 0; x--) {
			for (int y = w-1; y >= 0; y--) {
				double v = f[x][y][60];
				for (int i = 20+y+1; i < 40; i++)
					v -= f[x][y][i] * val[x][i-20];
				if (x+1 < h) {
					for (int i = 40; i < 60; i++)
						v -= f[x][y][i] * val[x+1][i-40];
				}
				val[x][y] = v;
			}
		}
		
		DONE:
		for (int x = 0; x < h; x++) {
			for (int y = 0; y < w; y++) {
				if (g[x][y] == 'T')
				printf("%.9lf\n", val[x][y]);
			}
		}
		puts("");
	}
	return 0;
}
/*
3 2
20 20 20 40
X.X
T.T
4 5
12 33 28 27
....
.XX.
....
T..T
XTTX
*/ 
