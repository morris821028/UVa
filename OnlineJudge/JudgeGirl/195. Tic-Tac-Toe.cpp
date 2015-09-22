#include <stdio.h>
#define N 3
int main() {
	int n, x, y;
	int g[N][N] = {}, ret = 0;
	scanf("%d", &n);
	for (int i = 0, j = 0, c; i < n; i++) {
		scanf("%d %d", &x, &y);
		if (ret || x < 0 || y < 0 || x >= N || y >= N)
			continue;
		c = j%2 + 1;
		if (g[x][y] == 0)
			g[x][y] = c, j++;
		int d1 = 1, d2 = 1;
		for (int i = 0; i < N; i++) {
			int ok1 = 1, ok2 = 1;
			for (int j = 0; j < N; j++)
				ok1 &= g[i][j] == c, ok2 &= g[j][i] == c;
			if (ok1 || ok2)	ret = c;
			d1 &= g[i][i] == c, d2 &= g[i][N-i-1] == c;
		}
		if (d1 || d2)	ret = c;
	}
	char s[3][32] = {"There is a draw.", "Black wins.", "White wins."};
	puts(s[ret]);
	return 0;
}
