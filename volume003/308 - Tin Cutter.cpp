#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

int g[512][512][4] = {}; /* up, down, left, right*/
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
void drawLine(int lx, int ly, int rx, int ry) {
	if(lx == rx) {
		for(int i = ly; i < ry; i++)
			g[lx][i][0] = g[lx-1][i][1] = 1;
	} else {
		for(int i = lx; i < rx; i++)
			g[i][ly][2] = g[i][ly-1][3] = 1;
	}
}

int cover[512][512] = {};
void dfs(int x, int y, int c, int n, int m) {
	if(x < 0 || y < 0 || x > n || y > m)
		return ;
	if(cover[x][y])		return;
	cover[x][y] = c;
	for(int i = 0; i < 4; i++) {
		if(g[x][y][i])	continue;
		dfs(x + dx[i], y + dy[i], c, n, m);
	}
}

int p[512], r[512];
void init(int n) {
    for(int i = 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        if(r[x] > r[y])
            p[y] = x, r[x] += r[y];
        else
            p[x] = y, r[y] += r[x];
        return 1;
    }
    return 0;
}
int main() {
	int n, X1[105], X2[105], Y1[105], Y2[105];
	while(scanf("%d", &n) == 1 && n) {
		memset(g, 0, sizeof(g));
		memset(cover, 0, sizeof(cover));
		map<int, int> RX, RY;
		for(int i = 0; i < n; i++) {
			scanf("%d %d %d %d", X1+i, Y1+i, X2+i, Y2+i);
			if(X1[i] == X2[i]) {
				if(Y1[i] > Y2[i])	swap(Y1[i], Y2[i]);
			} else {
				if(X1[i] > X2[i])	swap(X1[i], X2[i]);
			}
			RX[X1[i]] = RX[X2[i]] = 0;
			RY[Y1[i]] = RY[Y2[i]] = 0;
		}
		int sizex = 1, sizey = 1, prevx, prevy;
		for(map<int, int>::iterator it = RX.begin();
			it != RX.end(); it++)
			it->second = sizex++;
			
		for(map<int, int>::iterator it = RY.begin();
			it != RY.end(); it++)
			it->second = sizey++;
			
		for(int i = 0; i < n; i++) {
			int lx, ly, rx, ry;
			lx = RX[X1[i]], ly = RY[Y1[i]];
			rx = RX[X2[i]], ry = RY[Y2[i]];
			drawLine(lx, ly, rx, ry);
		}
		
		int c = 0;
		dfs(0, 0, ++c, sizex, sizey); // wall
		for(int i = 0; i <= sizex; i++)
			for(int j = 0; j <= sizey; j++)
				if(cover[i][j] == 0)
					dfs(i, j, ++c, sizex, sizey);
		
		int ret = c;
		init(c);
		for(int i = 0; i <= sizex; i++) {
			for(int j = 0; j <= sizey; j++) {
				for(int k = 0; k < 4; k++) {
					int rx, ry;
					rx = i + dx[k], ry = j + dy[k];
					if(rx < 0 || ry < 0 || rx > sizex || ry > sizey)
						continue;
					if(cover[i][j] == 1 || cover[rx][ry] == 1)
						continue;
					ret -= joint(cover[i][j], cover[rx][ry]);
				}
			}
		}
		
		printf("%d\n", ret - 1);
	}
	return 0;
}
/*
4
0 1 1 1
1 1 1 0
1 0 0 0
0 0 0 1
8
0 1 1 1
1 1 1 0
1 0 0 0
0 0 0 1
1 1 1 2
1 2 2 2
2 2 2 1
2 2 1 1
*/
