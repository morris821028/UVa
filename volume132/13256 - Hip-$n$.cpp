#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
int8_t g[MAXN][MAXN];
int n;
int A[MAXN*MAXN][2], an;
int B[MAXN*MAXN][2], bn;
inline int in_range(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < n;
}
int test(int p) {
	if (p == 1) {
		int ox = A[an-1][0], oy = A[an-1][1];
		for (int i = 0; i < an-1; i++) {
			int dx = A[i][0] - ox;
			int dy = A[i][1] - oy;
			int tx = ox - dy, ty = oy + dx;
			if (in_range(tx, ty) && g[tx][ty] == 1) {
				tx = tx + dx, ty = ty + dy;
				if (in_range(tx, ty) && g[tx][ty] == 1)
					return 1;
			}
			tx = ox + dy, ty = oy - dx;
			if (in_range(tx, ty) && g[tx][ty] == 1) {
				tx = tx + dx, ty = ty + dy;
				if (in_range(tx, ty) && g[tx][ty] == 1)
					return 1;
			}
		}
	} else {
		int ox = B[bn-1][0], oy = B[bn-1][1];
		for (int i = 0; i < bn-1; i++) {
			int dx = B[i][0] - ox;
			int dy = B[i][1] - oy;
			int tx = ox - dy, ty = oy + dx;
			if (in_range(tx, ty) && g[tx][ty] == 2) {
				tx = tx + dx, ty = ty + dy;
				if (in_range(tx, ty) && g[tx][ty] == 2)
					return 2;
			}
			tx = ox + dy, ty = oy - dx;
			if (in_range(tx, ty) && g[tx][ty] == 2) {
				tx = tx + dx, ty = ty + dy;
				if (in_range(tx, ty) && g[tx][ty] == 2)
					return 2;
			}
		}
	}
	return 0;
}
int main() {
	while (scanf("%d", &n) == 1) {
		memset(g, 0, sizeof(g));
		an = 0, bn = 0;
		int ret = 0;
		for (int i = 0; i < n*n; i++) {
			int x, y, p = (i&1)+1;
			scanf("%d %d", &x, &y);
			if (ret)
				continue;
			g[x][y] = p;
			if (p == 1)
				A[an][0] = x, A[an][1] = y, an++;
			else
				B[bn][0] = x, B[bn][1] = y, bn++;
			ret = test(p);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
1  0  1  1  2  1  0  2  0  1  2  0  0  0  1  2  2  2
3
1  0  1  1  2  1  0  2  0  1  2  0  1  2  0  0  2  2
3
1  0  2  2  2  1  0  0  1  2  0  2  1  1  2  0  0  1
*/
