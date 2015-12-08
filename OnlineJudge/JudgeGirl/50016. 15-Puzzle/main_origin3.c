#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAXN 4
const int dir[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
int g[MAXN][MAXN];
int K, ox, oy;
int solved = 0;
void swap(int *x, int *y) {int t; t = *x, *x = *y, *y = t;}
int isComplete() {
	int k = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (g[i][j] != (k&15))
				return 0;
			k++;
		}
	}
	return 1;
}
int simpleH() {
	int m = 1, diff = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (g[i][j] != (m&15))
				diff++;
			m++;
		}
	}
	return diff - 1;
}
int dfs(int dep, int ox, int oy) {
	if (isComplete()) {
		solved = 1;
		return 1;
	}
	if (dep + simpleH() > K)	return 0;
	for (int i = 0; i < 4; i++) {
		int tx, ty;
		tx = ox + dir[i][0], ty = oy + dir[i][1];
		if (tx < 0 || ty < 0 || tx >= MAXN || ty >= MAXN)
			continue;
		swap(&g[tx][ty], &g[ox][oy]);
		dfs(dep+1, tx, ty);
		swap(&g[tx][ty], &g[ox][oy]);
	}
	return 0;
}
int main() {
	while (scanf("%d", &K) == 1) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				scanf("%d", &g[i][j]);
				if (g[i][j] == 0)
					ox = i, oy = j;
			}
		}
		solved = 0;
		int ret = dfs(0, ox, oy);
		printf("%d\n", solved);
	}
	return 0;
}
