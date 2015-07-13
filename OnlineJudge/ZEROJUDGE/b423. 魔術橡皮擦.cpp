#include <bits/stdc++.h>
using namespace std;
int X, Y, TYPE, DIFF;
namespace Image {
	const int MAXN = 256;
	int n, m, rgba[MAXN][MAXN][4], used[MAXN][MAXN] = {};
	int RGB_diff(int x, int y, int a, int b) {
		return (rgba[x][y][0]-rgba[a][b][0])*(rgba[x][y][0]-rgba[a][b][0])+
				(rgba[x][y][1]-rgba[a][b][1])*(rgba[x][y][1]-rgba[a][b][1])+
				(rgba[x][y][2]-rgba[a][b][2])*(rgba[x][y][2]-rgba[a][b][2]);
	}
	void gTransparent(int x, int y, long long diff) {
		if (x < 0 || y < 0 || x >= m || y >= n || diff < 0)
			return ;
		diff = diff * diff;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (RGB_diff(x, y, i, j) <= diff)
					rgba[i][j][3] = 0;
	}
	void lTransparent(int x, int y, int ox, int oy, long long diff) {
		if (ox < 0 || oy < 0 || ox >= m || oy >= n || diff < 0)
			return ;
		static const int dx[] = {0, 0, 1, -1};
		static const int dy[] = {1, -1, 0, 0};
		if (x < 0 || y < 0 || x >= m || y >= n)
			return ;
		if (RGB_diff(x, y, ox, oy) > diff * diff || used[x][y])
			return ;
		rgba[x][y][3] = 0, used[x][y] = 1;
		for (int i = 0; i < 4; i++)
			lTransparent(x+dx[i], y+dy[i], ox, oy, diff);
	}
	void print() {
		printf("%d %d\n", n, m);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				printf("%d %d %d %d%c", rgba[i][j][0], rgba[i][j][1], rgba[i][j][2], rgba[i][j][3], j == n-1 ? '\n' : ' ');
		}
	}
}
int main() {
	scanf("%d %d %d %d", &X, &Y, &TYPE, &DIFF);
	scanf("%d %d", &Image::n, &Image::m);
	for (int i = 0; i < Image::m; i++)
		for (int j = 0; j < Image::n; j++)
			for (int k = 0; k < 4; k++)
				scanf("%d", &Image::rgba[i][j][k]);
	swap(X, Y);
	if (TYPE == 0)
		Image::gTransparent(X, Y, DIFF);
	if (TYPE == 1)
		Image::lTransparent(X, Y, X, Y, DIFF);
	Image::print();
	return 0;
}
