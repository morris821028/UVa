#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;
char g[1024][1024];
char node[1024 * 1024];
int build(int k, int lx, int ly, int rx, int ry) {
	if (lx == rx && ly == ry)
		return node[k] = (1<<g[lx][ly]);
	int mx = (lx + rx)/2, my = (ly + ry)/2;
	int v = 0;
	v |= build(k * 4, lx, ly, mx, my);
	v |= build(k * 4 + 1, mx + 1, ly, rx, my);
	v |= build(k * 4 + 2, lx, my + 1, mx, ry);
	v |= build(k * 4 + 3, mx + 1, my + 1, rx, ry);
	return node[k] = v;
}
void dfs(int u) {
	if (node[u] == 3) {
		if (u > 1)	putchar('*');	
		dfs(u * 4);
		dfs(u * 4 + 1);
		dfs(u * 4 + 2);
		dfs(u * 4 + 3);
	} else {
		if (node[u] == 1)
			putchar('0');
		else
			putchar('1');
	}
}
int main()  {
	int testcase;
	int n, sx, sy, ex, ey;
	char line[32767];
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		gets(line);
		stringstream sin(line);
		string token;
		sin >> n;
		if (__builtin_popcount(n) != 1 || n <= 1) {
			puts("Size is invalid");
			continue;
		}
		memset(g, 0, sizeof(g));
		while (sin >> token) {
			sscanf(token.c_str(), "(%d,%d)", &sx, &sy);
			if(sin >> token) {
				sscanf(token.c_str(), "(%d,%d)", &ex, &ey);
				sx--, sy--, ex--, ey--;
				for (int i = sx; i <= ex; i++)
					for (int j = sy; j <= ey; j++)
						g[i][j] = 1;
			}
		}
		build(1, 0, 0, n - 1, n - 1);
		dfs(1);
		puts("");
	}
	return 0;
}
