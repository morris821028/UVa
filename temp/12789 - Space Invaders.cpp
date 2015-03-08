// disjoint set
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
#define MAXN 1024
#define MAXM 131072
char g[MAXN][MAXN];
int A[MAXM], B[MAXM];
int parent[MAXN*MAXN], weight[MAXN*MAXN];
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
int findp(int x) {
	return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
}
int col[MAXN][MAXN], colIdx[MAXN][2];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, s;
	while (scanf("%d %d %d", &n, &m, &s) == 3) {
		memset(colIdx, 0, sizeof(colIdx));
		for (int i = 1; i <= n; i++) {
			scanf("%s", g[i] + 1);
			g[i][0] = g[i][m+1] = '#';
			for (int j = 1; j <= m; j++) {
				if (g[i][j] == '#') {
//					col[j].push_back(i);
					col[j][colIdx[j][1]++] = i;
				}
			}
		}
		for (int i = 0; i < s; i++) {
			scanf("%d", &A[i]), B[i] = -1;
			int x = abs(A[i]), y;
			if (colIdx[x][0] < colIdx[x][1]) {
				if (A[i] > 0)
					B[i] = col[x][colIdx[x][0]++];
				else
					B[i] = col[x][--colIdx[x][1]];
				g[B[i]][x] = '.';
//				printf("shot %d %d\n", B[i], A[i]);
			}
		}		
				
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m+1; j++) {
				int x = i * MAXN + j;
				parent[x] = x, weight[x] = 1;
//				printf("%c", g[i][j]);
			}
//			puts("--");
		}
		
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= m+1; j++) {
				if (g[i][j] == '#') {
					int u = i * MAXN + j, v, x, y;
					for (int k = 0; k < 8; k++) {
						x = i + dx[k], y = j + dy[k];
						if (1 <= x && x <= n && 0 <= y && y <= m+1 && g[x][y] == '#') {
							v = x * MAXN + y;
							joint(u, v);
//							printf("%d %d - %d %d, %d %d\n", i, j, x, y, u, v);
						}
					}
				}
			}
		}
		
		int left = 1 * MAXN + 0, right = 1 * MAXN + m+1;
		if (findp(left) == findp(right)) {
			puts("X");
			continue;
		}
		
		// reverse order, merge
		int flag = 0;
		for (int i = s-1; i >= 0; i--) {
			if (B[i] == -1)		continue;
			int x = abs(B[i]), y = abs(A[i]), u, v, tx, ty;
			u = x * MAXN + y;
			g[x][y] = '#';
			for (int k = 0; k < 8; k++) {
				tx = x + dx[k], ty = y + dy[k];
				if (1 <= tx && tx <= n && 0 <= ty && ty <= m+1 && g[tx][ty] == '#') {
					v = tx * MAXN + ty;
					joint(u, v);
				}
			}
			if (findp(left) == findp(right)) {
				printf("%d\n", A[i] < 0 ? -(i+1) : (i+1));
				flag = 1;
				break;
			}
		}
		if (!flag)
			puts("0");
	}
	return 0;
}
/*
2 2 2
.#
..
1
1
2 3 2
##.
.##
2
-2

2 3 2
##.
.##
-2
2

2 1 1
#
#
-1

10 5 10
####.
#...#
.#.#.
#....
...##
.#.##
.#...
.#...
#..#.
.....
-5
3
-4
-1
2
3
3
4
3
1
*/
