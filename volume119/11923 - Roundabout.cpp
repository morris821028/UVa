#include <bits/stdc++.h>
using namespace std;

static int src_blue, src_red;
static int cnt_blue, cnt_red;
static int g[4][4];
int score(int x, int y, int c) {
	int ret = 0;
	const int dx[] = {1, 0, 1, -1};
	const int dy[] = {0, 1, 1, 1};
	for (int i = 0; i < 4; i++) {
		int cc = 1, sx, sy, has = 0;
		sx = x+dx[i], sy = y+dy[i];
		for (; sx >= 0 && sy >= 0 && sx < 4 && sy < 4;) {
			if (g[sx][sy] != c)
				break;
			has |= 1;
			cc += g[sx][sy] == c;
			sx += dx[i], sy += dy[i];
		}
		sx = x-dx[i], sy = y-dy[i];
		for (; sx >= 0 && sy >= 0 && sx < 4 && sy < 4;) {
			if (g[sx][sy] != c)
				break;
			has |= 2;
			cc += g[sx][sy] == c;
			sx -= dx[i], sy -= dy[i];
		}
		if (cc == 3) {
			ret += 3;
		} else if (cc == 4) {
			ret += 7;
			if (has == 3)
				ret += 3;
		}
	}
	return ret;
}
void fill(int src, int dest) {
	int mx = -1, rx, ry;
	for (int i = 0; i < 4; i++)  {
		for (int j = 0; j < 4; j++) {
			if (g[i][j] == src) {
				int tmp = score(i, j, dest);
				if (tmp > mx)
					mx = tmp, rx = i, ry = j;
			}
		}
	}
	
	if (src == 0)
		cnt_blue--;
	else if (src == 1)
		cnt_red--;
		
	if (dest == 0)
		cnt_blue++, src_blue += mx;
	else if (dest == 1)
		cnt_red++, src_red += mx;
	assert(mx >= 0);
	g[rx][ry] = dest;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		char cmd[1024];
		scanf("%s", cmd);
		src_blue = src_red = 0;
		cnt_blue = cnt_red = 0;
		memset(g, -1, sizeof(g));
		for (int i = 0; cmd[i]; i++) {
			if (cmd[i] == '0')
				continue;
			if (i%2 == 0) {
				if (cnt_blue == 16) {
					src_blue += 50;
				} else if (cnt_blue+cnt_red < 16) {
					fill(-1, 0);
				} else {
					fill(1, 0);
				}
			} else {
				if (cnt_red == 16) {
					src_red += 50;
				} else if (cnt_blue+cnt_red < 16) {
					fill(-1, 1);
				} else {
					fill(0, 1);
				}
			}
		}
		printf("Case %d: %d %d\n", ++cases, src_blue, src_red);
	}
	return 0;
}
/*
4
10101010
011011001111
11111111
010111
*/
