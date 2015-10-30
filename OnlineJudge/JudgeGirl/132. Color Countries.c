#include <stdio.h>
#include <string.h>

int g[32][32], color[32];
int N, P, M;
int dfs(int u, int idx) {
	if (idx == N) {
		for (int i = 0; i < N; i++)
			printf("%d\n", color[i]);
		return 1;
	}
	int can[32] = {};
	int adj1 = -1, adj2 = -1;
	for (int i = 0; i < N; i++) {
		if (i == u)	continue;
		if (g[u][i] && color[i])
			can[color[i]] = 1;
		if (g[u][i] && color[i] == 0)
			adj1 = i;
		if (color[i] == 0)
			adj2 = i;
	}
	for (int i = 1; i <= P; i++) {
		if (can[i])	continue;
		color[u] = i;
		if (adj1 != -1) {
			if (dfs(adj1, idx+1))
				return 1;
		} else {
			if (dfs(adj2, idx+1))
				return 1;
		}
		color[u] = 0;
	}	
	return 0;
}
int main() {
	int x, y;
	while (scanf("%d %d %d", &N, &P, &M) == 3) {
		memset(g, 0, sizeof(g));
		memset(color, 0, sizeof(color));
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			if (x == y)	continue;
			g[x][y] = g[y][x] = 1;
		}
		int f = dfs(0, 0);
		if (!f)	
			puts("no solution.");
	}
	return 0;
}
