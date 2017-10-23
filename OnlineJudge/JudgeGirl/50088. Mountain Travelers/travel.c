#include "travel.h"
#include <stdint.h>

#define MAXN 1024
static const int dx[] = {0, 0, 1, -1, 1, -1, -1, 1};
static const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};
static int8_t used[MAXN][MAXN];

static inline int ufill(int g[][MAXN], int n, int m, int x, int y) {
	int ret = -1, mx = 0;
	int c = g[x][y];
	for (int i = 0; i < 8; i++) {
		int tx = x+dx[i], ty = y+dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= m)
			continue;
		if (g[tx][ty]-c > mx)
			mx = g[tx][ty]-c, ret = i;
	}
	return ret;
}
static inline int dfill(int g[][MAXN], int n, int m, int x, int y) {
	int ret = -1, mx = 0;
	int c = g[x][y];
	for (int i = 0; i < 8; i++) {
		int tx = x+dx[i], ty = y+dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= m)
			continue;
		if (c-g[tx][ty] > mx)
			mx = c-g[tx][ty], ret = i;
	}
	return ret;
}
void travel(int g[][MAXN], int n, int m, int ax, int ay, 
			int bx, int by, int dirA[], int dirB[]) {
	used[ax][ay] = used[bx][by] = 1;
	int aDir = 0, bDir = 0;
	while (aDir != -1 || bDir != -1) {
		if (aDir != -1)
			aDir = ufill(g, n, m, ax, ay);
		if (bDir != -1)
			bDir = dfill(g, n, m, bx, by);
		if (aDir >= 0) {
			ax += dx[aDir], ay += dy[aDir];
			dirA[0] = aDir, dirA++;
			if (used[ax][ay] == 0)
				used[ax][ay] = 1;
			else
				aDir = -1;
		}
		if (bDir >= 0) {
			bx += dx[bDir], by += dy[bDir];
			dirB[0] = bDir, dirB++;
			if (used[bx][by] == 0)
				used[bx][by] = 1;
			else
				bDir = -1;
		}
		if (ax == bx && ay == by)
			aDir = bDir = -1;
	}
	dirA[0] = -1, dirB[0] = -1;
}
