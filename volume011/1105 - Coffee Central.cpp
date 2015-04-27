#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 2048;
int sum[MAXN][MAXN];
void rotate(int x, int y, int &tx, int &ty, int dx, int dy) {
	tx = x - y + dy, ty = x + y;
}
void query(int limit, int dx, int dy) {
	int ret = 0, ret_x = 1, ret_y = 1;
	int tx, ty;
	for (int j = 1; j <= dy; j++) {
		for (int i = 1; i <= dx; i++) {
			rotate(i, j, tx, ty, dx, dy);
			int lx, rx, ly, ry, cnt;
			lx = max(tx - limit, 1);
			ly = max(ty - limit, 1);
			rx = min(tx + limit, dx + dy);
			ry = min(ty + limit, dx + dy);
			cnt = sum[rx][ry] - sum[rx][ly-1] - sum[lx-1][ry] + sum[lx-1][ly-1];
			if (cnt > ret) {
				ret = cnt, ret_x = i, ret_y = j;
			}
		}
	}
	printf("%d (%d,%d)\n", ret, ret_x, ret_y);
}
int main() {
	int dx, dy, n, q;
	int x, y, tx, ty, limit, cases = 0;
	while (scanf("%d %d %d %d", &dx, &dy, &n, &q) == 4 && dx) {
		// rotate matrix, rotate 45 degree
//		for (int i = 1; i <= dx; i++) {
//			for (int j = 1; j <= dy; j++) {
//				printf("(%d %d) -> (%d %d)\n", i, j, i - j + dy, i + j);
//			} 
//		}

		memset(sum, 0, sizeof(sum));
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			rotate(x, y, tx, ty, dx, dy);
			sum[tx][ty]++;
		}
		
		for (int i = 1; i <= dx + dy; i++) {
			for (int j = 1, s = 0; j <= dx + dy; j++) {
				s += sum[i][j];
				sum[i][j] = sum[i-1][j] + s;
			}
		}
		
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			scanf("%d", &limit);
			query(limit, dx, dy);
		}
	}
	return 0;
}
