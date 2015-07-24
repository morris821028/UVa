#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};
const int dy[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
char g[2048][2048], ret[2048][2048];
int FAST(int x, int y) {
	char c[4] = {g[x+dx[0]][y+dy[0]], g[x+dx[4]][y+dy[4]], 
				g[x+dx[8]][y+dy[8]], g[x+dx[12]][y+dy[12]]};
	if (c[0] == c[1] && c[1] == c[2] || 
		c[1] == c[2] && c[2] == c[3] ||
		c[2] == c[3] && c[3] == c[0] ||
		c[3] == c[0] && c[0] == c[1]) {
		int cc = -1, p = 1;
		for (int it = 1, i = 1, j = 0; it < 16; it++, i++, i = i >= 16 ? 0 : i) {
			if (g[x+dx[i]][y+dy[i]] == g[x+dx[j]][y+dy[j]])
				j ++, j = j >= 16 ? 0 : j, p++;
			else {
				if (cc == -1)
					cc = p;
				j = i, p = 1;
			}
			if (p >= 12)
				return 1;
		}
		if (g[x+dx[0]][y+dy[0]] == g[x+dx[15]][y+dy[15]] && p+cc >= 12)
			return 1;
	}
	return 0;
}
int main() {
	int N, M, cases = 0;
	while (scanf("%d %d", &N, &M) == 2) {
		while (getchar() != '\n');
		for (int i = 0; i < N; i++)
			fgets(g[i], 2000, stdin);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				ret[i][j] = '0';
				if (i-3 >= 0 && j-3 >= 0 && i+3 < N && j+3 < M)
					ret[i][j] = FAST(i, j) + '0';
			}
		}
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < N; i++) {
			ret[i][M] = '\0';
			puts(ret[i]);
		}
	}
	return 0;
}

