#include <bits/stdc++.h>
using namespace std;
const int dx[] = {1, 1, -1, -1};
const int dy[] = {-1, 1, 1, -1};
int main() {
	int n, m;
	while (scanf("%d %d", &m, &n) == 2) {
		int A[32][32];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &A[i][j]);
		int sx, sy, dir;
		int ret = 0;
		scanf("%d %d %d", &sy, &sx, &dir);
		sx--, sy--, dir--;
		for (int bound = 0; bound <= 3; ) {
//			printf("%d %d %d --\n", sx, sy, A[sx][sy]);
			ret += A[sx][sy];
			sx += dx[dir], sy += dy[dir];
//			printf("next %d %d\n", sx, sy);
			if (sx < 0 || sy < 0 || sx >= n || sy >= m) {
				bound++;
				if (sx >= 0 && sx < n) {
					sy = max(min(sy, m-1), 0);
					if (dir == 0 || dir == 2)
						dir = (dir+1)%4;
					else
						dir = (dir+3)%4;
				} else if (sy >= 0 && sy < m) {
					sx = max(min(sx, n-1), 0);
					if (dir == 1 || dir == 3)
						dir = (dir+1)%4;
					else
						dir = (dir+3)%4;
				} else {
					sx -= dx[dir], sy -= dy[dir];
					dir = (dir+2)%4;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3 3
1 3 9
-4 -6 5
8 2 -7
3 1 1

3 4
2 5 8
3 -1 -6
7 8 -9
2 0 3
1 1 2

3 4
2 5 8
3 -1 -6
7 8 -9
2 0 3
2 1 1
*/

