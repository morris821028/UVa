#include <stdio.h> 
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

const int MAXN = 20;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0}; 
char sg[MAXN][MAXN][4][8];
int dist[MAXN][MAXN][4];
int toDir(char c) {
	switch(c) {
		case 'E': return 0;
		case 'S': return 1;
		case 'W': return 2;
		case 'N': return 3;
	}
	return -1;
}
void bfs(int dir, int sx, int sy, int ex, int ey) {
	queue<int> X, Y, D;
	memset(dist, 0, sizeof(dist));
	X.push(sx), Y.push(sy), D.push(dir);
	dist[sx][sy][dir] = 1;
	while (!X.empty()) {
		sx = X.front(), X.pop();
		sy = Y.front(), Y.pop();
		dir = D.front(), D.pop();
		if (sx == ex && sy == ey) {
			printf("%d\n", dist[sx][sy][dir]);
			return ;
		}
		for (int i = 0; sg[sx][sy][dir][i]; i++) {
			int d = toDir(sg[sx][sy][dir][i]);
			int tx, ty, td;
			tx = sx + dx[d], ty = sy + dy[d];
			td = (d + 2)%4;
			if (dist[tx][ty][td] == 0) {
				dist[tx][ty][td] = dist[sx][sy][dir]+1;
				X.push(tx), Y.push(ty), D.push(td);
			}
		} 
	}
	puts("Are you kidding me?");
}
int main() {
	int testcase;
	int n, m, q, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d %d", &x, &y);
				for (int k = 0; k < 4; k++)
					scanf("%s", &sg[x][y][k]);
			}
		}
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			int ex, ey, sx, sy;
			char s[8];
			scanf("%s %d %d %d %d", &s, &sx, &sy, &ex, &ey);
			bfs(toDir(s[0]), sx, sy, ex, ey);
		}
		puts("----------");
	}
	return 0;
}
/*
2
3 3
0 0 S E E E
0 1 W E ES S
0 2 SW W S S
1 0 NS N ES E
1 1 W NEW SE W
1 2 W NW N W
2 0 N N NE E
2 1 W E N E
2 2 NW N N W
2
N 0 0 2 2
W 1 1 0 0
3 4
0 0 S E E ES
0 1 W E S W
0 2 S W S S
0 3 SW W S W
1 0 N NE NS ES
1 1 NS N NS E
1 2 N N N S
1 3 N N N SW
2 0 N N E E
2 1 N EW NE E
2 2 N NEW N EW
2 3 W NW N W
2
E 0 2 2 0
N 0 1 1 0 
*/
