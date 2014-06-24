#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXV 128
enum STATE {EMPTY, LOCK, BACK, UNLOCK};
int g[MAXV][MAXV][MAXV];
int W, H, T, N;
const int dx[] = {0, 0, 1, -1, 0};
const int dy[] = {1, -1, 0, 0, 0};
void dfs1(int time, int x, int y) {
	if(time == 1 || g[time][x][y] == BACK) {
		g[time][x][y] = BACK;
		return;
	}
	for(int i = 0, tx, ty; i < 5; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if(tx <= 0 || ty <= 0 || tx > W || ty > H)
			continue;
		if(g[time-1][tx][ty] == LOCK)
			continue;
		g[time][x][y] = BACK;
		dfs1(time - 1, tx, ty);
	}
}
void dfs2(int time, int x, int y) {
	if(time == T || g[time][x][y] == UNLOCK) {
		g[time][x][y] = UNLOCK;
		return;
	}
	for(int i = 0, tx, ty; i < 5; i++) {
		tx = x + dx[i], ty = y + dy[i];
		if(tx <= 0 || ty <= 0 || tx > W || ty > H)
			continue;
		if(g[time+1][tx][ty] == LOCK)
			continue;
		if(g[time+1][tx][ty] == BACK || g[time+1][tx][ty] == UNLOCK) {
			g[time][x][y] = UNLOCK;
			dfs2(time + 1, tx, ty);
		}
	}
}
int main() {
	int cases = 0;
	int left, top, right, bottom, t;
	while(scanf("%d %d %d", &W, &H, &T) == 3 && W+H+T) {
		scanf("%d", &N);
		for(int i = 1; i <= T; i++)
			for(int j = 1; j <= W; j++)
				for(int k = 1; k <= H; k++)
					g[i][j][k] = EMPTY;
		for(int i = 0; i < N; i++) {
			scanf("%d %d %d %d %d", &t, &left, &top, &right, &bottom);
			for(int j = left; j <= right; j++)
				for(int k = top; k <= bottom; k++)
					g[t][j][k] = LOCK;
		}
		
		for(int i = 1; i <= W; i++)
			for(int j = 1; j <= H; j++)
				if(g[T][i][j] != LOCK)
					dfs1(T, i, j);
		for(int i = 1; i <= W; i++)
			for(int j = 1; j <= H; j++)
				if(g[1][i][j] == BACK)
					dfs2(1, i, j);
					
		printf("Robbery #%d:\n", ++cases);		
		int f = 1;
		for(int i = 1; i <= T; i++) {
			int e = 0, rx, ry;
			for(int j = 1; j <= W; j++) {
				for(int k = 1; k <= H; k++) {
					if(g[i][j][k] == UNLOCK)
						e++, rx = j, ry = k;
				}
			}
			if(e == 0) {
				puts("The robber has escaped.");
				f = 0;
				break;
			}
			if(e == 1) {
				printf("Time step %d: The robber has been at %d,%d.\n", i, rx, ry);
				f = 0;
			}
		}
		if(f)
			puts("Nothing known.");
		puts("");
	}
	return 0;
}
/*
4 4 5
4
1 1 1 4 3
1 1 1 3 4
4 1 1 3 4
4 4 2 4 4
10 10 3
1
2 1 1 10 10
0 0 0
*/
