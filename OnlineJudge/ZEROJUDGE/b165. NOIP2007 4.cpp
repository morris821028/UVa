#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, s;
	int x, y, v;
	while (scanf("%d %d", &n, &s) == 2) {
		int g[305][305];
		memset(g, 0x3f, sizeof(g));
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &x, &y, &v);
			g[x][y] = g[y][x] = v;
		}
		
		for (int i = 1; i <= n; i++)
			g[i][i] = 0;
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
		
		int ret = INT_MAX;
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				if (g[i][j] <= s) {
					int ECC = 0;
					for (int k = 1; k <= n; k++)
						ECC = max(ECC, g[i][k] + g[k][j] - g[i][j]);
					ret = min(ret, ECC/2);
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
