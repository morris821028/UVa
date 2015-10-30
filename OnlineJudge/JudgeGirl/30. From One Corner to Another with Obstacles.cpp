#include <stdio.h>

int g[16][16] = {};
int dfs(int n, int m) {
	if (n < 0 || m < 0 || g[n][m] == 0)
		return 0;
	if (n == 0 && m == 0)
		return 1;
	return dfs(n-1, m) + dfs(n, m-1);
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = n-1; i >= 0; i--) {
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		}
		printf("%d\n", dfs(n-1, m-1));
	}
	return 0;
}

