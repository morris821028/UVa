#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
char g[16][16];
int bg[16][16], dirg[16][16][4][3], blueAll, blueCnt;
int short_path[16][16][32];
const int dx[] = {0, -1, 1, 0};
const int dy[] = {1, 0, 0, -1};
const int dmask[] = {4, 8, 2, 1};
const char dstr[] = "ENSW";
void buildDirg(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 4; k++) {
				int blue = 0;
				int sx = i, sy = j;
				while (true) {
					if (bg[sx][sy])
						blue |= 1<<(bg[sx][sy]-1);
					if (g[sx][sy]&dmask[k])
						break;
					sx += dx[k], sy += dy[k];
				}
				dirg[i][j][k][0] = sx;
				dirg[i][j][k][1] = sy;
				dirg[i][j][k][2] = blue;
			}
		}
	}
}
void buildHfun(int n) {
	memset(short_path, 0x3f, sizeof(short_path));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			queue<int> X, Y;
			int dist[16][16], sx, sy, tx, ty;
			memset(dist, 0x3f, sizeof(dist));
			X.push(i), Y.push(j), dist[i][j] = 0;
			if (bg[i][j])
				short_path[i][j][bg[i][j]-1] = min(short_path[i][j][bg[i][j]-1], 0);
			while (!X.empty()) {
				sx = X.front(), X.pop();
				sy = Y.front(), Y.pop();
				for (int p = 0; p < 4; p++) {
					tx = sx, ty = sy;
					while (true) {
						if (bg[tx][ty])	
							short_path[i][j][bg[tx][ty]-1] = min(short_path[i][j][bg[tx][ty]-1], dist[sx][sy] + 1);
						if (g[tx][ty]&dmask[p])
							break;
						tx += dx[p], ty += dy[p];
					}						
					if (dist[tx][ty] > dist[sx][sy] + 1) {
						dist[tx][ty] = dist[sx][sy] + 1;
						X.push(tx), Y.push(ty);
					}
				}
			}
		}
	}
}
int ida_dep, solved;
char path[1024];
int H(int sx, int sy, int bstate) {
	int ret = 0;
	for (int i = 0; i < blueCnt; i++) {
		if ((bstate>>i)&1)	continue;
		ret = max(ret, short_path[sx][sy][i]);
	}
	return ret;
}
map<int, int> record[16][16]; // [sx][sy][bstate] = minstep
int IDA(int sx, int sy, int bstate, int dep, int hv, int dlast) {
	if (hv == 0) {
		path[dep] = '\0';
		puts(path);
		solved = dep;
		return dep;
	}

	if (dep + hv > ida_dep)	return dep + hv;
	
	map<int, int>::iterator it = record[sx][sy].find(bstate);
	if (it == record[sx][sy].end())
		record[sx][sy][bstate] = dep;
	else {
		if (it->second <= dep)	return 0x3f3f3f3f;
		else					it->second = dep;
	}
	
	int ret = 0x3f3f3f3f, shv, tmp;
	for (int i = 0; i < 4; i++) {
		if (i == dlast)	continue;
		path[dep] = dstr[i];
		shv = H(dirg[sx][sy][i][0], dirg[sx][sy][i][1], bstate|dirg[sx][sy][i][2]);
		tmp = IDA(dirg[sx][sy][i][0], dirg[sx][sy][i][1], bstate|dirg[sx][sy][i][2], dep+1, shv, i);
		if (solved)	return solved;
		ret = min(ret, tmp);
	}
	return ret;
}
int main() {
	int n, next_n, sx, sy, ex, ey;
	char s[1024];
	scanf("%d", &n);
	while (n) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		scanf("%d %d", &sx, &sy);
		sx--, sy--;
		memset(bg, 0, sizeof(bg));
		while (getchar() != '\n');
		while (gets(s)) {
			if (sscanf(s, "%d %d", &ex, &ey) == 2) {
				ex--, ey--;
				bg[ex][ey] = 1;
			} else if (sscanf(s, "%d", &next_n) == 1)
				break;
		}
		blueAll = blueCnt = 0;
		int bx[128], by[128];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (bg[i][j]) {
					bx[blueCnt] = i, by[blueCnt] = j;
					blueCnt++, bg[i][j] = blueCnt, blueAll |= 1<<(blueCnt-1);
				}
				if ('0' <= g[i][j] && g[i][j] <= '9')
					g[i][j] -= '0';
				else if(g[i][j] >= 'A' && g[i][j] <= 'Z')
					g[i][j] = g[i][j] - 'A' + 10;
			}
		}
		
		buildDirg(n);
		buildHfun(n);
		
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				for (int k = 0; k < blueCnt; k++) {
//					printf("%d %d to %d %d = %d\n", i, j, bx[k], by[k], short_path[i][j][k]);
//				}
//			}
//		}
		
		int bstate = 0;
		if (bg[sx][sy])	bstate = 1<<(bg[sx][sy]-1);
		int initH = H(sx, sy, bstate);
		if (initH == 0) {
			puts("SOLVED");
		} else {
			solved = 0;
			ida_dep = initH;
			while (solved == 0) {
				ida_dep = IDA(sx, sy, bstate, 0, initH, 4);
				for (int i = 0; i < n; i++) // not tradition ida*
					for (int j = 0; j < n; j++)
						record[i][j].clear();
			}
		}
		n = next_n;
	}
	return 0;
}
/*
5
9AC9C
18006
5120C
12806
3A63E
1 1
5 5
0

8
9A88CB8C
18610824
30804184
90430004
10080457
1430000C
53800245
3A263A26
6 4
4 1
8 1
2 2
7 3
4 4
1 5
7 5
5 6
3 7
8 7
2 8
4 8
6
98E98E
30A00C
908047
10430C
710804
B63677
4 1
1 3
3 6
5
9AC9C
18006
5120C
12806
3A63E
1 1
5 5
0
*/
