// IDA, Bfs
#include <stdio.h> 
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int dx[] = {1, 1, -1, -1, 3, 3, -3, -3};
const int dy[] = {3, -3, 3, -3, 1, -1, 1, -1};
const int px[] = {1, 1, -1, -1, 1, 1, -1, -1};
const int py[] = {1, -1, 1, -1, 1, -1, 1, -1};
int hdist[16][16][16][16];
vector< pair<int, int> > g[16][16];
int move(int n, int m, int x, int y, int kind, int &rx, int &ry) {
	int tx, ty;
	tx = x + dx[kind], ty = y + dy[kind];
	if (tx < 0 || ty < 0 || tx >= n || ty >= m)
		return 0;
	rx = tx, ry = ty;
	tx = x, ty = y;
//	for (int i = 0; i < 2; i++) {
//		tx = tx + px[kind], ty = ty + py[kind];
//		if (tx < 0 || ty < 0 || tx >= n || ty >= m)
//			return 0;
//	}
	return 1;
}
void moveBfs(int n, int m, int sx, int sy) {
	int x, y, tx, ty;
	int dist[16][16] = {};
	const int INF = 0x3f3f3f3f;
	queue<int> X, Y;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dist[i][j] = INF;
			
	X.push(sx), Y.push(sy), dist[sx][sy] = 0;
	while (!X.empty()) {
		x = X.front(), y = Y.front();
		X.pop(), Y.pop();
		for (int i = 0; i < 8; i++) {
			if (move(n, m, x, y, i, tx, ty)) {
				if (dist[tx][ty] > dist[x][y] + 1) {
					dist[tx][ty] = dist[x][y] + 1;
					X.push(tx), Y.push(ty);
				}
			}
		}
	}
	
	// record sssp
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			hdist[sx][sy][i][j] = dist[i][j];
		}
	}
}

#define MAXL (100>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[5500], Pt = 0;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 100;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			for (k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
			P[Pt++] = i;
		}
	}
}

// IDA

int ida_depth, solved;
int used[16][16];
int IDA(int x, int y, int ex, int ey, int dep, int hv) {
    if (hv == 0) {
        if (!GET(dep)) {
        	solved = 1;
        	return dep;
        }
        return 0x3f3f3f3f;
        return dep;
    }
    if (dep + hv > ida_depth)
        return dep + hv;
    int back = 0x3f3f3f3f, shv, tmp;
    for (int i = 0; i < g[x][y].size(); i++) {
    	int tx = g[x][y][i].first, ty = g[x][y][i].second;
        shv = hdist[tx][ty][ex][ey];
        
        if (used[tx][ty])
        	continue;
        	
        used[tx][ty] = 1;
        tmp = IDA(tx, ty, ex, ey, dep + 1, shv);
        used[tx][ty] = 0;
        
        back = min(back, tmp);
        if (solved) return back;
    }
    return back;
}


int main() {
	sieve();
	int n, m, sx, sy, ex, ey;
	int cases = 0;
	while (scanf("%d %d %d %d %d %d", &n, &m, &sx, &sy, &ex, &ey) == 6) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				moveBfs(n, m, i, j);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				g[i][j].clear();
				for (int k = 0; k < 8; k++) {
					int tx, ty;
					if (move(n, m, i, j, k, tx, ty))
						g[i][j].push_back(make_pair(tx, ty));
				}
			}
		}
		
//		printf("Bfs %d\n", hdist[sx][sy][ex][ey]);
//		for (int i = 0; i < n; i++, puts(""))
//			for (int j = 0; j < m; j++)
//				printf("%d ", hdist[sx][sy][i][j] == 0x3f3f3f3f ? -1 : hdist[sx][sy][i][j]);
		
		printf("CASE# %d: ", ++cases);
		
		if (hdist[sx][sy][ex][ey] > 1 && hdist[sx][sy][ex][ey] < 100 && !GET(hdist[sx][sy][ex][ey])) {
			printf("The knight takes %d prime moves.\n", hdist[sx][sy][ex][ey]);
			continue;
		}
				
		solved = 0;
		if (hdist[sx][sy][ex][ey] != 0x3f3f3f3f && (sx != ex || sy != ey)) {
			memset(used, 0, sizeof(used)); 
			
			used[sx][sy] = 1;
			ida_depth = 0;
			for (int i = 0; i < Pt && P[i] < 11; i++) {
				if (P[i] < ida_depth)
					continue;
				ida_depth = P[i];
				ida_depth = IDA(sx, sy, ex, ey, 0, hdist[sx][sy][ex][ey]);
				
				if (solved) {
					printf("The knight takes %d prime moves.\n", P[i]);
					break;
				}
			}
		}
		if (!solved) {
			if (hdist[sx][sy][ex][ey] == 0x3f3f3f3f)
				printf("Destination is not reachable.\n");
			else
				printf("The knight takes %d composite move(s).\n", hdist[sx][sy][ex][ey]);
		}
	}
	return 0;
} 

/*
5 7 2 2 3 1

5 5 0 0 3 4
5 5 0 0 4 4
5 5 0 0 0 0

8 4 4 0 3 2
4 8 1 1 3 5
5 7 2 2 3 1
7 8 0 7 0 5
7 5 1 4 0 4
5 6 1 4 0 2
6 4 0 2 0 1
8 8 1 0 2 7
8 5 0 1 6 1
7 8 1 5 1 4

*/
