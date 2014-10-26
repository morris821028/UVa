#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;
char g[1024][1024];
char line[32767];
int idx;
void build(int k, int lx, int ly, int rx, int ry) {
	char type = line[idx++];
	if (type == '*') {
		int mx = (lx + rx)/2, my = (ly + ry)/2;
		build(k * 4, lx, ly, mx, my);
		build(k * 4 + 1, mx + 1, ly, rx, my);
		build(k * 4 + 2, lx, my + 1, mx, ry);
		build(k * 4 + 3, mx + 1, my + 1, rx, ry);
	} else {
		for (int i = lx; i <= rx; i++)
			for (int j = ly; j <= ry; j++)
				g[i][j] = type;
	} 
}
int main() {	
	int testcase;
	int n, sx, sy, ex, ey;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		scanf("%d %s", &n, line);
		if (__builtin_popcount(n) != 1 || n <= 1) {
			puts("Invalid length");
			continue;
		}
		idx = 0;
		build(1, 0, 0, n-1, n-1);
		int f = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[j][i] == '1') {
					int l = j, r = j;
					while (r < n && g[r][i] == '1')
						r++;
					if (f)	putchar(',');
					f = 1;
					if (l + 1 != r)
						printf("(%d-%d,%d)", l+1, r, i+1);
					else
						printf("(%d,%d)", r, i+1);
					j = r;
				}
			}
		}
		puts("");
	}
	return 0;
}
