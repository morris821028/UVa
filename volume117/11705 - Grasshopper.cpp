#include <stdio.h> 
#include <queue>
#include <algorithm>
using namespace std;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const char ds[] = {'S', 'E', 'N', 'W'};
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, g[64][64];
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
				
		char ret[64][64] = {};
		int visited[64][64] = {}, x, y, tx, ty, d;
		int vx[64][64], vy[64][64];
		queue<int> X, Y;
		X.push(0), Y.push(0);
		while(!X.empty()) {
			x = X.front(), X.pop();
			y = Y.front(), Y.pop();
			for(int i = 0; i < 4; i++) {
				tx = x + dx[i], ty = y + dy[i], d = 1;
				while(tx < n && ty < m && tx >= 0 && ty >= 0) {
					if(g[tx][ty] == d) {
						if(visited[tx][ty] == 0) {
							visited[tx][ty] = visited[x][y] + 1;
							ret[tx][ty] = ds[i];
							vx[tx][ty] = x, vy[tx][ty] = y;
							X.push(tx), Y.push(ty);
						} else if(visited[tx][ty] == visited[x][y] + 1 
						&& make_pair(x, y) < make_pair(vx[tx][ty], vy[tx][ty])) {
							ret[tx][ty] = ds[i];
							vx[tx][ty] = x, vy[tx][ty] = y;
						}
					}
					tx += dx[i], ty += dy[i], d++;
				}
			}
		}
		for(int i = 0; i < n; i++, puts("")) {
			for(int j = 0; j < m; j++) {
				if(i == 0 && j == 0)
					putchar('*');
				else if(visited[i][j] == 0)
					putchar('X');
				else
					putchar(ret[i][j]);
			}
		}
		puts("");
	}
	return 0;
}
