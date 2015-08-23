#include <bits/stdc++.h>
using namespace std;
const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {-1, 1, 0, 1, -1, 0, 1, -1};
int main() {
	char g[64][64];
	int N = 15, M = 30;
	for (int i = 0; i < N; i++)
		scanf("%s", g[i]);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (g[i][j] == '.') {
				int tx, ty, cnt = 0;
				for (int k = 0; k < 8; k++) {
					tx = i + dx[k], ty = j + dy[k];
					if (tx < 0 || ty < 0 || tx >= N || ty >= M)
						continue;
					if (g[tx][ty] == '*')
						cnt++;
				}
				if (cnt)
					g[i][j] = cnt + '0';
			}
		}
	}
	for (int i = 0; i < N; i++)
		puts(g[i]);
	return 0;
}
