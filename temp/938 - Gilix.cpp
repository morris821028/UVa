#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

int g[512][512];
int dist[512][512][2], inq[512][512][2];
const int dx1[] = {-1, -1, 0, 1, 1, 0};
const int dy1[] = {0, 1, 1, 1, 0, -1};
const int dx2[] = {-1, -1, 0, 1, 1, 0};
const int dy2[] = {-1, 0, 1, 0, -1, -1};
void spfa(int L, int C, int sx, int sy, int ex, int ey, int px, int py) {
	memset(dist, 63, sizeof(dist));
	queue<int> X, Y, S;
	int tx, ty, ts, ss;
	dist[sx][sy][0] = 0;
	X.push(sx), Y.push(sy), S.push(0);
	while (!X.empty()) {
		sx = X.front(), X.pop();
		sy = Y.front(), Y.pop();
		ss = S.front(), S.pop();
		inq[sx][sy][ss] = 0;
		for (int i = 0; i < 6; i++) {
			if (sx&1)
				tx = sx + dx1[i], ty = sy + dy1[i];
			else
				tx = sx + dx2[i], ty = sy + dy2[i];
			if (tx < 0 || tx >= L)	continue;
			ty = (ty + C)%C;
			ts = ss;
			int cost = ts ? g[tx][ty]/2 : g[tx][ty];
			if (tx == px && ty == py)
				ts = ss | 1;
			if (dist[tx][ty][ts] > dist[sx][sy][ss] + cost) {
				dist[tx][ty][ts] = dist[sx][sy][ss] + cost;
				if (!inq[tx][ty][ts]) {
					inq[tx][ty][ts] = 1;
					X.push(tx), Y.push(ty), S.push(ts);
				}
			}
		}
	}
	printf("%d\n", min(dist[ex][ey][0], dist[ex][ey][1]));
}
int main() {
	int L, C;
	int sx, sy, ex, ey, px, py;
	while (scanf("%d %d", &L, &C) == 2) {
		for (int i = 0; i < L; i++) {
			for (int j = 0; j < C; j++)
				scanf("%d", &g[i][j]);
		}
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		scanf("%d %d", &px, &py);
		spfa(L, C, sx, sy, ex, ey, px, py);
	}
	return 0;
}
/*
4 8
4 2 2 2 4 4 6 10
2 6 8 4 4 4 4 2
8 2 6 8 4 4 4 6
6 4 4 6 8 4 4 4
0 0
3 4
1 1
*/
