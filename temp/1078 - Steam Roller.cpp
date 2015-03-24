#include <stdio.h> 
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int MAXN = 128;
int cg[MAXN][MAXN][4];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int dist[MAXN][MAXN][4][2], inq[MAXN][MAXN][4][2];
int spfa(int r1, int c1, int r2, int c2) {
	if (r1 == r2 && c1 == c2)
		return 0;
	queue<int> X, Y, D, F;
	int d1, f1, x, y, w;
	memset(dist, 63, sizeof(dist));
	memset(inq, 0, sizeof(inq));
	for (int i = 0; i < 4; i++) {
		if (!cg[r1][c1][i])	continue;
		x = r1 + dx[i], y = c1 + dy[i];
		dist[x][y][i][1] = 2 * cg[r1][c1][i];
		inq[x][y][i][1] = 1;
		X.push(x), Y.push(y), D.push(i), F.push(1);
	}
	
	while (!X.empty()) {
		r1 = X.front(), X.pop();
		c1 = Y.front(), Y.pop();
		d1 = D.front(), D.pop();
		f1 = F.front(), F.pop();
		inq[r1][c1][d1][f1] = 0;
//		printf("%d %d %d %d - %d\n", r1, c1, d1, f1, dist[r1][c1][d1][f1]); 
		for (int i = 0; i < 4; i++) {
			if (!cg[r1][c1][i])	continue;
			x = r1 + dx[i], y = c1 + dy[i];
//			printf("-> %d %d\n", x, y);
			if (f1 == 1) {
				if (i == d1) {
					w = cg[r1][c1][i] + dist[r1][c1][d1][f1];
					if (dist[x][y][i][0] > w) {
						dist[x][y][i][0] = w;
						if (!inq[x][y][i][0]) {
							inq[x][y][i][0] = 1;
							X.push(x), Y.push(y), D.push(i), F.push(0);
						}
					}
				}
				w = 2 * cg[r1][c1][i] + dist[r1][c1][d1][f1];					
				if (dist[x][y][i][1] > w) {
					dist[x][y][i][1] = w;
					if (!inq[x][y][i][1]) {
						inq[x][y][i][1] = 1;
						X.push(x), Y.push(y), D.push(i), F.push(1);
					}
				}
			} else {
				if (i != d1)	continue;
				w = cg[r1][c1][i] + dist[r1][c1][d1][f1];
				if (dist[x][y][i][0] > w) {
					dist[x][y][i][0] = w;
					if (!inq[x][y][i][0]) {
						inq[x][y][i][0] = 1;
						X.push(x), Y.push(y), D.push(i), F.push(0);
					}
				}
				
				w = 2 * cg[r1][c1][i] + dist[r1][c1][d1][f1];					
				if (dist[x][y][i][1] > w) {
					dist[x][y][i][1] = w;
					if (!inq[x][y][i][1]) {
						inq[x][y][i][1] = 1;
						X.push(x), Y.push(y), D.push(i), F.push(1);
					}
				}
			}
		}
	}
	
	int ret = 0x3f3f3f3f;
	for (int i = 0; i < 4; i++)
		ret = min(ret, dist[r2][c2][i][1]);
	return ret == 0x3f3f3f3f ? -1 : ret;
}
int main() {
	int R, C, r1, c1, r2, c2;
	int x, cases = 0;
	while (scanf("%d %d %d %d %d %d", &R, &C, &r1, &c1, &r2, &c2) == 6 && R) {
		memset(cg, 0, sizeof(cg));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C - 1; j++) {
				scanf("%d", &x);
				cg[i][j][0] = cg[i][j+1][1] = x;
			}
			if (i != R - 1) {
				for (int j = 0; j < C; j++) {
					scanf("%d", &x);
					cg[i][j][2] = cg[i+1][j][3] = x;
				}
			}
		}
		
		r1--, c1--, r2--, c2--;
		int d = spfa(r1, c1, r2, c2);
		printf("Case %d: ", ++cases);
		if (d >= 0)
			printf("%d\n", d);
		else
			printf("Impossible\n");
	}
	return 0;
}
/*
4 4 4 3 2 4
 7 6 2 
4 5 0 4 
 6 4 1 
4 4 2 2 
 9 4 4 
5 5 3 2 
 9 6 9 

4 4 1 1 4 4 
 10  10  10 
9  0  0  10 
  0  0  0 
9  0  0  10 
  9  0  0 
0  9  0  10 
  0  9  9 

4 4 1 1 1 2
 10  10  10 
9  0  0  10 
  0  0  0 
9  0  0  10 
  9  0  0 
0  9  0  10 
  0  9  9 
  
4 4 1 1 4 4
 10  10  10 
9  0  0  10 
  0  0  0 
9  0  0  10 
  9  0  0 
0  9  0  0 
  0  9  9 
*/
