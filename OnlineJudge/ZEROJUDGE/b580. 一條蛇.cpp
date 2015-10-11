#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int g[128][128];
		int x = n/2, y = n/2;
		g[x][y] = 1, y++;
		for (int it = 2, vv = 2; vv <= n*n; it+=2) {
			for (int i = 0; i < it; i++)
				g[x][y] = vv, x--, vv++;
			x++, y--;
			for (int i = 0; i < it; i++)
				g[x][y] = vv, y--, vv++;
			x++, y++;
			for (int i = 0; i < it; i++)
				g[x][y] = vv, x++, vv++;
			x--, y++;
			for (int i = 0; i < it; i++)
				g[x][y] = vv, y++, vv++;
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				printf("%4d%c", g[i][j], " \n"[j==n-1]);
		}
	}
	return 0;
}

