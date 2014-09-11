#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;

char g[256][256];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};
int main() {
	int n, m, cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n + m) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		int tx, ty;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == '?') {
					int adj[26] = {}, ch = -1;
					for (int p = 0; p < 4; p++) {
						tx = i + dx[p], ty = j + dy[p];
						if (tx < 0 || ty < 0 || tx >= n || ty >= m)
							continue;
						if (g[tx][ty] != '?' && g[tx][ty] != '.')
							adj[g[tx][ty]-'A']++;
					}
					for (int p = 0; p < 26; p++) {
						if (adj[p] == 0) {
							ch = p;
							break;
						} 
					}
//					printf("ch %c\n", ch + 'A');
					for (int k = 0; i + k < n && j + k < m; k++) {
						int ok = 1;
						for (int p = 0; p <= k; p++) {
							if (g[i+k][j+p] != '?')	ok = 0;
							for (int q = 0; q < 3; q++) {
								tx = i+k + dx[q], ty = j+p + dy[q];
								if (tx < 0 || ty < 0 || tx >= n || ty >= m)
									continue;
								if (g[tx][ty] != '?' && g[tx][ty] != '.')
									adj[g[tx][ty]-'A']++;
							}
						}
						for (int p = 0; p < k; p++) {
							if (g[i+p][j+k] != '?')	ok = 0;
							for (int q = 1; q < 4; q++) {
								tx = i+p + dx[q], ty = j+k + dy[q];
								if (tx < 0 || ty < 0 || tx >= n || ty >= m)
									continue;
								if (g[tx][ty] != '?' && g[tx][ty] != '.')
									adj[g[tx][ty]-'A']++;
							}
						}
						if (adj[ch])	ok = 0;
						if (!ok) {
//							printf("obstacle %c\n", ch + 'A');
							break;
						}
						for (int p = 0; p <= k; p++)
							g[i+p][j+k] = g[i+k][j+p] = ch + 'A';
							
						int x = i, y = j + k + 1, alt = 0, aa;
						for (int p = 0; p < ch && y < m; p++) {
							int ok = 1;
							if (x-1 >= 0 && g[x-1][y] == p + 'A')
								ok = 0;
							if (y+1 < m && g[x][y+1] == p + 'A')
								ok = 0;
							if (x+1 < n && g[x+1][y] == p + 'A')
								ok = 0;
							if (ok) {
								alt = 1, aa = p;
								break;
							}
						}
						if (alt) {
//							printf("alt %c -> %c\n", ch + 'A', aa + 'A');
							break;
						}
					}
				}
			}
		}
		if (cases++)	puts("");
		for (int i = 0; i < n; i++)
			puts(g[i]);
	}
	return 0;
}
/*
5 5
????.
???.?
?????
?????
????.
5 5
?????
.???.
.???.
.???.
?????
0 0
*/
