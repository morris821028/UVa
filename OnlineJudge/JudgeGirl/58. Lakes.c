#include <stdio.h>
int n, m, g[512][512], L[262144];
int findc(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= m || g[x][y] != 1)
		return 0;
	g[x][y] = -1;
	return 1 + findc(x-1, y) + findc(x+1, y) + findc(x, y-1) + findc(x, y+1);
}
int cmp(const void *a, const void *b) {
	return *(int *)b - *(int *)a;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		int r = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] > 0)
					L[r++] = findc(i, j);
			}
		}
		qsort(L, r, sizeof(int), cmp);
		for (int i = 0; i < r; i++)
			printf("%d\n", L[i]);
	}
	return 0;
}
