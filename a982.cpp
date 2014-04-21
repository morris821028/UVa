#include <stdio.h> 
#include <queue>
using namespace std;

int main() {
	int n;
	char g[105][105];
	int dx[] = {0, 0, 1, -1};
	int dy[] = {1, -1, 0, 0};
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; i++)
			scanf("%s", &g[i]);
		queue<int> X, Y;
		int dist[105][105] = {};
		dist[1][1] = 1;
		X.push(1), Y.push(1);
		while(!X.empty()) {
			int x = X.front(), y = Y.front();
			X.pop(), Y.pop();
			for(int i = 0; i < 4; i++) {
				int tx, ty;
				tx = x + dx[i], ty = y + dy[i];
				if(tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == '#')
					continue;
				if(dist[tx][ty] == 0) {
					dist[tx][ty] = dist[x][y] + 1;
					X.push(tx), Y.push(ty);
				}
			}
		}
		if(dist[n-2][n-2])
			printf("%d\n", dist[n-2][n-2]);
		else
			puts("No solution!");
	}
	return 0;
}
