#include <stdio.h>
#define MAXN 4
#define swap(x, y) {int t; t = x, x = y, y = t;}
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int readboard(int g[][MAXN], int x[], int y[]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (scanf("%d", &g[i][j]) != 1)
				return 0;
			x[g[i][j]] = i, y[g[i][j]] = j;
		}
	}
	return 1;
}
int move(int v, int g[][MAXN], int x[], int y[]) {
	if (v <= 0 || v >= MAXN*MAXN)	return 0;
	int valid = 0, end = 1;
	for (int i = 0; i < 4; i++)
		if (x[0]+dx[i] == x[v] && y[0]+dy[i] == y[v])
			valid = 1;
	if (!valid)	return 0;
	swap(g[x[0]][y[0]], g[x[v]][y[v]]);
	swap(x[0], x[v]);
	swap(y[0], y[v]);
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++)
			end &= (g[i][j] == i*MAXN+j+1 || g[i][j] == 0);
	}
	return end;
}
int main() {
	int g[MAXN][MAXN], x[MAXN*MAXN+1], y[MAXN*MAXN+1], n, v;
	while (readboard(g, x, y)) {
		int end = 0, rc = 0;
		while (scanf("%d", &v) == 1 && v) {
			if (end == 0 && move(v, g, x, y))
				end = 1, rc = v;
		}
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
				printf("%d%c", g[i][j], " \n"[j==MAXN-1]);
		if (end)
			printf("%d %d\n", end, rc);
		else
			printf("%d\n", end);
	}
	return 0;
}

