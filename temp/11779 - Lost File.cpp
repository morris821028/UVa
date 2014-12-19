#include <stdio.h> 
// inverse floyd-warshall algorithm
int main() {
	int testcase, cases = 0;
	int n, m, g[64][64];
	int x, y, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i][j] = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x][y] += w;
		}
		
		for (int k = 0; k < n; k++) { 
			for (int i = 0; i < n; i++) {
				if (g[i][k])
				for (int j = 0; j < n; j++)
					g[i][j] -= g[i][k] * g[k][j];
			}
		} 
		int e = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				e += g[i][j];
		printf("Case %d: %d %d\n", ++cases, n, e);
		for (int i = 0; i < n; i++) {
			int cnt = 0;
			for (int j = 0; j < n; j++)
				cnt += g[i][j];
			printf("%d", cnt);
			for (int j = 0; j < n; j++)
				if (g[i][j])
					printf(" %d", j);
			puts("");
		}
	}
	return 0;
}
