#include <stdio.h> 
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 1600
char g[MAXN][MAXN];
int sum[3][MAXN][MAXN], n, m;
int used[MAXN][MAXN] = {};
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
void bfs(queue<int> &X, queue<int> &Y, int l, int cases) {
	int x, y, tx, ty;
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		for (int i = 0; i < 8; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if (tx <= 0 || ty <= 0 || tx > n || ty > m)
				continue;	
			sum[l][tx][ty] = 1;
			if (g[tx][ty] == '#' && used[tx][ty] != cases) {
				used[tx][ty] = cases;
				X.push(tx), Y.push(ty);
			}
		}
	}
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1, s = 0; j <= m + 1; j++) {
			s += sum[l][i][j];
			sum[l][i][j] = sum[l][i-1][j] + s;
		}
	}
}
void prepare() {
	static int cases = 0;
	queue<int> X, Y;
	++cases;
	for (int i = 1; i <= m; i++)
		X.push(0), Y.push(i), used[0][i] = cases;
	for (int i = 1; i <= n; i++)
		X.push(i), Y.push(m+1), used[i][m+1] = cases;
	bfs(X, Y, 1, cases);
	++cases;
	for (int i = 1; i <= m; i++)
		X.push(n+1), Y.push(i), used[n+1][i] = cases;
	for (int i = 1; i <= n; i++)
		X.push(i), Y.push(0), used[i][0] = cases;
	bfs(X, Y, 2, cases);
}
int findMaxSquare(int lx, int ly, int r, int lv) {
	int mid = 0, l = 0, ret = 0;
	int s = 0;
	while (l <= r) {
		mid = (l + r) /2;
		s = sum[lv][lx+mid][ly+mid] - sum[lv][lx-1][ly+mid]
			- sum[lv][lx+mid][ly-1] + sum[lv][lx-1][ly-1];
		if (!s)
			l = mid + 1, ret = mid;
		else
			r = mid - 1;
	}
	if (lx + ret >= n && ly + ret >= m)
		ret--;
	return ret + 1;
}
int ok(int lx, int ly, int &w) {
	w--;
	while (lx + w > n || ly + w > m)
		w--;
	if (lx + w >= n && ly + w >= m)
		w--;
	if (w < 0)	return 0;
	int s1, s2, s3;
	s1 = sum[0][lx+w][ly+w] - sum[0][lx-1][ly+w]
		- sum[0][lx+w][ly-1] + sum[0][lx-1][ly-1];
	s2 = sum[1][lx+w][ly+w] - sum[1][lx-1][ly+w]
		- sum[1][lx+w][ly-1] + sum[1][lx-1][ly-1];
	s3 = sum[2][lx+w][ly+w] - sum[2][lx-1][ly+w]
		- sum[2][lx+w][ly-1] + sum[2][lx-1][ly-1];
	w++;
	return s1 == 0 && s2 && s3;
}
int main() {
	while (scanf("%d %d", &m, &n) == 2) {
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		for (int i = 0; i <= n + 1; i++)
			for (int j = 0; j <= m + 1; j++) 
				sum[0][i][j] = sum[1][i][j] = sum[2][i][j] = 0;
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1, s = 0; j <= m; j++) {
				s += g[i][j] == '#';
				sum[0][i][j] = sum[0][i-1][j] + s;
			} 
		}
		prepare();
		
		int ret = 0x3f3f3f3f, rx = -1, ry = -1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (i == 1 && j == 1)	continue;
				if (g[i][j] == '#')
					continue;
				int maxs = min(min(n - i, m - j) + 1, ret - 1);
				int maxe = findMaxSquare(i, j, maxs, 0);
				int mins = max(findMaxSquare(i, j, maxe, 1), findMaxSquare(i, j, maxe, 2)) + 1;
				mins = min(mins, maxe);
				if (mins < ret && ok(i, j, mins)) {
					ret = mins, rx = i, ry = j;
				}
			}
		}
		if (rx != -1)
			printf("%d %d %d\n", ret, ry, rx);
		else
			puts("Impossible");
	}
	return 0;
}
/*
11 6
......#####
.#.#...#..#
.#.#.......
.......###.
#####.###..
#####......
3 3
...
.#.
...
13 13
.............
.#.##.####.##
.#..#...#....
.####.#.##.##
....#.#..#...
##.##.##.#.##
....######.#.
#.#..#..##.#.
..####.##....
#..#...#####.
##.###.#.##..
.###.#....##.
.......##....

*/
