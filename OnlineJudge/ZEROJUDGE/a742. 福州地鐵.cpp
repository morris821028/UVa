#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char g[MAXN][MAXN][4];
int used[MAXN][MAXN];
int main() {
	int N, M, SX, SY, EX, EY, K;
	while (scanf("%d %d", &N, &M) == 2) {
		scanf("%d %d %d %d", &SX, &SY, &EX, &EY);
		scanf("%d", &K);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				memset(g[i][j], 0, sizeof(g[0][0]));
			for (int j = 0; j < M; j++)
				used[i][j] = 0;
		}
		
		for (int i = 0; i < K; i++) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 == x2) {
				if (y1 > y2)	swap(y1, y2);
				for (int j = y1; j < y2; j++)
					g[x1][j][0] = g[x1][j+1][1] = 1;
			} else {
				assert(y1 == y2);
				if (x1 > x2)	swap(x1, x2);
				for (int j = x1; j < x2; j++)
					g[j][y1][2] = g[j+1][y1][3] = 1;
			}
		}
		
		int x, y, tx, ty;
		queue<int> X, Y;
		X.push(SX), Y.push(SY);
		while (!X.empty()) {
			x = X.front(), X.pop();
			y = Y.front(), Y.pop();
			for (int i = 0; i < 4; i++) {
				if (g[x][y][i])
					continue;
				tx = x + dx[i], ty = y + dy[i];
				if (tx < 0 || ty < 0 || tx >= N || ty >= M)
					continue;
				if (used[tx][ty] == 0) {
					used[tx][ty] = used[x][y]+1;
					X.push(tx), Y.push(ty);
				}
			}
		}
		if (used[EX][EY])
			printf("%d\n", used[EX][EY]);
		else
			puts("10080");
	}
	return 0;
}
/*
4 5 0 0 2 4 6
0 0 0 1
0 1 3 1
0 3 3 3
3 3 3 4
1 1 1 3
2 1 2 3
*/
