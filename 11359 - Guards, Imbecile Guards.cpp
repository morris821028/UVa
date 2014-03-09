#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int N;
char g[20][20];
struct DataX {
	int vx[3], vy[3], dir[3];
};
DataX cycle[1024];
int cycle_len;
int dist[10][10][1024];
void bfs() {
	int sx = 0, sy = 0, cc, ncc;
	int tx, ty;
	int i, j, k;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(g[i][j] == 'S')
				sx = i, sy = j;
			for(k = 0; k < cycle_len; k++)
				dist[i][j][k] = 0;
		}
	}
	queue<int> X, Y, C;
	dist[sx][sy][0] = 1;
	X.push(sx), Y.push(sy), C.push(0);
	int dx[] = {0, 0, 1, -1, 0};
	int dy[] = {1, -1, 0, 0, 0};
	while(!X.empty()) {
		sx = X.front(), sy = Y.front(), cc = C.front();
		X.pop(), Y.pop(), C.pop();
		ncc = (cc+1)%cycle_len;
		for(i = 0; i < 5; i++) {
			tx = sx + dx[i], ty = sy + dy[i];
			if(tx < 0 || ty < 0 || tx >= N || ty >= N || g[tx][ty] == '#')
				continue;
			int ok = 1;
			for(j = 0; j < 3 && ok; j++) {
				if(tx == cycle[ncc].vx[j] && ty == cycle[ncc].vy[j])
					ok = 0;
				if(cycle[ncc].vx[j] == sx && cycle[ncc].vy[j] == sy &&
					cycle[cc].vx[j] == tx && cycle[cc].vy[j] == ty)
					ok = 0; // cross (cause bump into each other during a move)
			}
			if(ok) {
				if(dist[tx][ty][ncc] == 0) {
					dist[tx][ty][ncc] = dist[sx][sy][cc] + 1;
					if(g[tx][ty] == 'T') {
						printf("%d\n", dist[sx][sy][cc]);
						return;
					}
					X.push(tx), Y.push(ty), C.push(ncc);
				}
			}
		}
	}
	puts("-1");
}
int main() {
	int testcase, cases = 0;
	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		memset(cycle, -1, sizeof(cycle));
		cycle_len = 1;
		int m = 0;
		for(i = 0; i < N; i++) {
			scanf("%s", g[i]);
			for(j = 0; j < N; j++) {
				if(g[i][j] == 'X') {
					if(j+1 >= N || g[i][j+1] == '#') {
						if(j-1 < 0 || g[i][j-1] == '#') {
							g[i][j] = '#';
							continue;
						}
					}
					cycle[0].vx[m] = i;
					cycle[0].vy[m] = j;
					cycle[0].dir[m] = 1; // next direction right.
					if(j+1 >= N || g[i][j+1] == '#')
						cycle[0].dir[m] = 0; // next direction left.
					m++;
				}
			}
		}
		do {
			int CC = cycle_len;
			DataX &r = cycle[CC];
			for(i = 0; i < m; i++) {
				r.vx[i] = cycle[CC-1].vx[i];
				r.vy[i] = cycle[CC-1].vy[i] + (cycle[CC-1].dir[i] ? 1 : -1);
				r.dir[i] = cycle[CC-1].dir[i];
				int nx = r.vx[i], ny = r.vy[i] + (r.dir[i] ? 1 : -1);
				if(ny >= N || g[nx][ny] == '#' || ny < 0 || g[nx][ny] == '#')
					r.dir[i] = !r.dir[i];
			}
			int same = 1;
			for(i = 0; i < m; i++) {
				same &= r.vx[i] == cycle[0].vx[i];
				same &= r.vy[i] == cycle[0].vy[i];
				same &= r.dir[i] == cycle[0].dir[i];
			}
			if(same)	break;
			cycle_len++;
		} while(true);
		printf("Case %d: ", ++cases);
		bfs();
	}
	return 0;
}
