#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int R[32], C[32], g[32][32];
int n, m, n2, used[128];

int dfs(int x, int y) {
	if (y == m) {
		if (R[x])	return 0;
		y = 0, x++;
	}
	if (x == n-1 && y > 0 && C[y-1])
		return 0;
	if (x == n) {
		if (C[m-1])
			return 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				printf("%d%c", g[i][j], " \n"[j == m-1]);
		return 1;
	}
	for (int i = 1; i <= n2; i++) {
		if (used[i] || R[x] < i || C[y] < i)
			continue;
		R[x] -= i, C[y] -= i, g[x][y] = i;
		used[i] = 1;
		if (dfs(x, y+1))
			return 1;
		R[x] += i, C[y] += i;
		used[i] = 0;
	}
	return 0;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < n; i++)
			scanf("%d", &R[i]), sum1 += R[i];
		for (int i = 0; i < m; i++)
			scanf("%d", &C[i]), sum2 += C[i];
			
		memset(used, 0, sizeof(used));
		n2 = n*m;
		if (sum1 != n2*(n2+1)/2 || sum2 != n2*(n2+1)/2) {
			printf("no solution\n");
		} else {
			int f = dfs(0, 0);
			if (f == 0)
				printf("no solution\n");
		}
	}
	return 0;
}


