#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int R[32], C[32], g[32][32];
int n, m, n2, used[128];
int Rn[32], Cn[32];
int min(int x, int y) {return x < y ? x : y;}
int dfs(int idx) {
	if (idx == n*m) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				printf("%d%c", g[i][j], " \n"[j == m-1]);
		}
		return 1;
	}
	
	int x, y, mn = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i][j])
				continue;
			int t = min(R[i], C[j]);
			if (t < mn)
				mn = t, x = i, y = j;
		}
	}
	
	for (int t = 1; t <= mn; t++) {
		if (used[t])
			continue;
		if (Rn[x] == 1 && R[x] != t)
			continue;
		if (Cn[y] == 1 && C[y] != t)
			continue;
		R[x] -= t, C[y] -= t;
		used[t] = 1, g[x][y] = t, Rn[x]--, Cn[y]--;
		if (dfs(idx+1))
			return 1;
		R[x] += t, C[y] += t;
		used[t] = 0, g[x][y] = 0, Rn[x]++, Cn[y]++;
	}
	return 0;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < n; i++)
			scanf("%d", &R[i]), sum1 += R[i], Rn[i] = m;
		for (int i = 0; i < m; i++)
			scanf("%d", &C[i]), sum2 += C[i], Cn[i] = n;
		
		memset(used, 0, sizeof(used));
		memset(g, 0, sizeof(g));
		n2 = n*m;
		if (sum1 != n2*(n2+1)/2 || sum2 != n2*(n2+1)/2) {
			printf("no solution\n");
		} else {
			int f = dfs(0);
			if (f == 0)
				printf("no solution\n");
		}
	}
	return 0;
}
