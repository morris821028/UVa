#include <stdio.h> 
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

char g[128][128], player[128];
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};

int computeSp(int x, int y, int dir) {
	int tx, ty, sp = 0;
	tx = x, ty = y;
	while (tx < 8 && ty < 8 && tx >= 0 && ty >= 0)
		sp += g[tx][ty] != '.', tx += dx[dir], ty += dy[dir];
	tx = x - dx[dir], ty = y - dy[dir];
	while (tx < 8 && ty < 8 && tx >= 0 && ty >= 0)
		sp += g[tx][ty] != '.', tx -= dx[dir], ty -= dy[dir];
	return sp;
}
int main() {
	int cases = 0;
	while (scanf("%s", g[0]) == 1) {
		for (int i = 1; i < 8; i++)
			scanf("%s", g[i]);
		scanf("%s", player);
		
		vector<string> ret;
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (g[i][j] == player[0]) {
					for (int k = 0; k < 8; k++) {
						int sp = computeSp(i, j, k);
						int tx = i + dx[k] * sp, ty = j + dy[k] * sp;
						if (tx < 0 || ty < 0 || tx >= 8 || ty >= 8)
							continue;
						if (g[tx][ty] == player[0])
							continue;
						int ok = 1;
						for (int p = 1; p < sp && ok; p++) {
							tx = i + dx[k] * p, ty = j + dy[k] * p;
							if (g[tx][ty] != '.' && g[tx][ty] != player[0])
								ok = 0;
						}
						if (ok == 1) {
							tx = i + dx[k] * sp, ty = j + dy[k] * sp;
							char buf[16];
							sprintf(buf, "%c%d-%c%d", i+'A', j+1, tx+'A', ty+1);
							ret.push_back(buf);
						}
					}
				}
			}
		}
		
		sort(ret.begin(), ret.end());
		
		if (cases++)	puts("");
		if (ret.size() == 0)
			puts("No moves are possible");
		else {
			for (int i = 0; i < ret.size(); i++)
				puts(ret[i].c_str());
		}
	}
	return 0;
}
/*
O.......
O......X
O.....XX
O....XXX
.O...XXX
........
..O..XXX
........
O
..OXO...
..OOO...
........
........
........
........
........
........
X
........
........
........
........
........
........
........
........
O
*/
