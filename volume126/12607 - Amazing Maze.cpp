#include <stdio.h> 
#include <algorithm>
#include <queue>
#include <assert.h>
using namespace std;

const int dx[] = {-1, 0, 1, 0}; // N E S W 
const int dy[] = {0, 1, 0, -1};
int used[100][100][4][1<<8] = {}, testcase = 0;
int dist[100][100][4][1<<8] = {};
int main() {
	int N, M, K, x, y;
	char g[128][128];
	while (scanf("%d %d", &N, &M) == 2 && N+M) {
		int treasure[128][128] = {}, dirg[128][128] = {};
		for (int i = 0; i < N; i++) {
			scanf("%s", g[i]);
			for (int j = 0; j < M; j++) {
				if (g[i][j] == 'N')
					dirg[i][j] = 0;			
				if (g[i][j] == 'E')
					dirg[i][j] = 1;	
				if (g[i][j] == 'S')
					dirg[i][j] = 2;	
				if (g[i][j] == 'W')
					dirg[i][j] = 3;
			}
		}
		scanf("%d", &K);
		for (int i = 0; i < K; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			assert(treasure[x][y] == 0);
			treasure[x][y] = i + 1;
		}
		queue<int> X, Y, D, T;
		int x = 0, y = 0, d = 0, t = 0;
		int tx, ty, td, tt;
		if (treasure[x][y])
			t |= 1<<(treasure[x][y] - 1);
		X.push(x), Y.push(y), D.push(d), T.push(t);
		testcase++;
		used[x][y][d][t] = testcase;
		dist[x][y][d][t] = 0;
		while (!X.empty()) {
			x = X.front(), X.pop();
			y = Y.front(), Y.pop();
			d = D.front(), D.pop();
			t = T.front(), T.pop();	
					
			tx = x, ty = y, td = (d + 1)%4, tt = t;
			if (used[tx][ty][td][tt] != testcase) {
				used[tx][ty][td][tt] = testcase;
				dist[tx][ty][td][tt] = dist[x][y][d][t] + 1;
				X.push(tx), Y.push(ty), D.push(td), T.push(tt);
				if (tx == N - 1 && ty == M - 1 && tt == (1<<K) - 1)
					break;
			}
			
			int dir = (dirg[x][y] + d)%4;
			tx = x + dx[dir], ty = y + dy[dir], td = (d + 1)%4, tt = t;
			if (tx < 0 || ty < 0 || tx >= N || ty >= M)
				continue;
			if (treasure[tx][ty])
				tt |= 1<<(treasure[tx][ty] - 1);
			if (used[tx][ty][td][tt] != testcase) {
				used[tx][ty][td][tt] = testcase;
				dist[tx][ty][td][tt] = dist[x][y][d][t] + 1;
				X.push(tx), Y.push(ty), D.push(td), T.push(tt);
				if (tx == N - 1 && ty == M - 1 && tt == (1<<K) - 1)
					break;
			}
		}
		int ret = 0x3f3f3f3f;
		for (int i = 0; i < 4; i++) {
			if (used[N-1][M-1][i][(1<<K)-1] == testcase)
				ret = min(ret, dist[N-1][M-1][i][(1<<K)-1]);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 2
EE
NN
1
1 2

1 1
E
1
1 1

1 2
NE
1
1 2

0 0
*/
