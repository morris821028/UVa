#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 1024

int A[MAXN][MAXN], solv[MAXN][MAXN];
int g[MAXN][MAXN];
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
int n, m;
int isplace(int x, int y) {
	int v = A[x][y], tx, ty;
	int unknown = 0, score = 0;
	for (int i = 0; i < 8; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= m)
			continue;
		if (solv[tx][ty])	score += g[tx][ty];
		else				unknown++;
	}
	if (v < 3)					return -1;
	if (v > 8)					return 1;
	if (score + unknown < v)	return 1;
	if (score + 4 > v)			return -1;
	return 0; // not sure.
}
int main() {
	int testcase;
	int t;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &A[i][j]);
			}
		}
		memset(solv, 0, sizeof(solv));
		int test = n * m;
		while (test) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (solv[i][j])	continue;
					int t = isplace(i, j);
					if (t) {
						test--;
						g[i][j] = t > 0;
						solv[i][j] = 1;
					}
				}
			}
			
		}
		for (int i = 0; i < n; i++, puts("")) {
			for (int j = 0; j < m; j++) {
				if (solv[i][j])
					putchar(g[i][j] ? 'L' : '-');
				else {
					assert(false);
				}
			}
		}
	}
	return 0;
}
/*
9999
3 4
2 6 3 2
7 5 7 5
6 7 3 2

3 3
7 9 7
9 12 9
7 9 7

3 1
0
0
0

*/
