#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
int n, m, golygons;
set< pair<int, int> > ban;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
const char sdir[] = "nsew";
char path[1024];
char g[2048][2048] = {}, g2[2048][2048];
vector<string> ways;
#define BASE 1024
void dfs(int x, int y, int dir, int step) {
	if (abs(x - 0) + abs(y - 0) > (step + n) * (n - step + 1)/2) {
		return;
	}
	if (step == n + 1) {
		if (x == 0 && y == 0) {
			path[step - 1] = '\0';
//			puts(path);
			ways.push_back(path);
			golygons++;
		}
		return ;
	}
	if (dir != 0) {
		for (int i = 0; i < 2; i++) {
			int tx = x, ty = y, ok = 1;
			for (int j = 0; j < step; j++) {
				tx = tx + dx[i], ty = ty + dy[i];
				assert(BASE + tx >= 0 && BASE + ty >= 0);
				assert(BASE + tx < 2048 && BASE + ty < 2048);
				if (g[BASE + tx][BASE + ty]) {
					ok = 0;
					break;
				}
			}
			if (ok && g2[BASE + tx][BASE + ty] == 0) {
				g2[BASE + tx][BASE + ty] = 1;
				path[step - 1] = sdir[i];
				dfs(tx, ty, 0, step + 1);
				g2[BASE + tx][BASE + ty] = 0;
			}
		}
	}
	if (dir != 1) {
		for (int i = 2; i < 4; i++) {
			int tx = x, ty = y, ok = 1;
			for (int j = 0; j < step; j++) {
				tx = tx + dx[i], ty = ty + dy[i];
				assert(BASE + tx >= 0 && BASE + ty >= 0);
				assert(BASE + tx < 2048 && BASE + ty < 2048);
				if (g[BASE + tx][BASE + ty]) {
					ok = 0;
					break;
				}
			}
			if (ok && g2[BASE + tx][BASE + ty] == 0) {
				g2[BASE + tx][BASE + ty] = 1;
				path[step - 1] = sdir[i];
				dfs(tx, ty, 1, step + 1);
				g2[BASE + tx][BASE + ty] = 0;
			}
		}
	}
}
int main() {
	int testcase, x[64], y[64];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		ban.clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x[i], &y[i]);
			ban.insert(make_pair(x[i], y[i]));
			g[BASE + x[i]][BASE + y[i]] = 1;
		}
		ways.clear();
		dfs(0, 0, -1, 1);
		sort(ways.begin(), ways.end());
		for (int i = 0; i < ways.size(); i++)
			puts(ways[i].c_str());
		printf("Found %d golygon(s).\n\n", ways.size());
		for (int i = 0; i < m; i++)
			g[BASE + x[i]][BASE + y[i]] = 0;
	}
	return 0;
}
/*
2
8
2
-2 0
6 -2
8
2
2 1
-2 0

1000
16
0
*/
