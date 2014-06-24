#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
char g[700][700][4];
char visited[700][700];
void bfs(int x, int y, int n, int m) {
	queue<int> X, Y;
	X.push(x), Y.push(y);
	visited[x][y] = 1;
	while(!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		for(int i = 0, tx, ty; i < 4; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if(tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if(visited[tx][ty] || g[x][y][i])
				continue;
			visited[tx][ty] = 1;
			X.push(tx), Y.push(ty);
		}
	}
}
int main() {
	int N;
	char line[1024];
	while(scanf("%d", &N) == 1)	 {
		memset(g, 0, sizeof(g));
		memset(visited, 0, sizeof(visited));
		for(int i = 0; i < 2 * N - 1; i++) {
			scanf("%s", line);
			int x = i, y = x&1;
			for(int j = 0; j < N; j++, y += 2) {
				if(line[j] == 'H') {
					g[x][y][0] = g[x + 1][y][1] = 1;
					g[x][y + 1][0] = g[x + 1][y + 1][1] = 1;
				} else {
					g[x][y][2] = g[x][y + 1][3] = 1;
					g[x + 1][y][2] = g[x + 1][y + 1][3] = 1;
				}
			}
		}
		int cc = 0;
		for(int i = 0; i < 2 * N; i++) {
			for(int j = 0; j < 2 * N + 1; j++) {
				if(!visited[i][j])
					bfs(i, j, 2*N, 2*N+1), cc++;
			}
		}
		printf("%d\n", cc - 1);
	}
	return 0;
}
/*
3
HVH
VVV
HHH
HHH
VHV
1
H
1
V
*/
