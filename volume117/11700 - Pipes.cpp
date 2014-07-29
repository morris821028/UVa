#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int g[16][16][4], n, m;
int kind[16][16], solvable;
static const int dx[] = {-1, 0, 1, 0}; // N, E, S, W
static const int dy[] = {0, 1, 0, -1};
void rotate(int r, int c) {
	int t = g[r][c][0];
	for(int i = 1; i < 4; i++)
		g[r][c][i-1] = g[r][c][i];
	g[r][c][3] = t;
}
int check(int r, int c, int ign) {
	for(int i = 0; i < 4; i++) {
		if(i == ign)	continue;
		if(g[r][c][i]) {
			int tx = r + dx[i], ty = c + dy[i];
			if(tx < 0 || ty < 0 || tx >= n || ty >= m)
				return 0;
			if(!g[tx][ty][(i+2)%4])
				return 0;
		}
	}
	return 1;
}
void dfs(int r, int c) {
	if(solvable)
		return;
	if(c == m) {
		if(check(r, c-1, 2))
			dfs(r + 1, 0);
		return ;
	}
	if(r == n) {
		int f = 1;
		for(int i = 0; i < m; i++)
			f &= check(r-1, i, -1);
//		if(f)
//		for(int i = 0; i < n; i++) {
//			for(int j = 0; j < m; j++) {
//				printf("[%d, %d] ", i, j);
//				for(int k = 0; k < 4; k++)
//					printf(" %d", g[i][j][k]);
//				puts("");
//			}
//		}
		solvable |= f;
		return;
	}
	
	if(kind[r][c] == 0) {
		if(check(r-1, c, -1)) {
			if(c && !check(r, c-1, 2))
				return;
			dfs(r, c+1);
		}
	} else {
		for(int i = 0; i < kind[r][c]; i++, rotate(r, c)) {
			if(check(r-1, c, -1)) {
				if(c && !check(r, c-1, 2))
					continue;
				dfs(r, c+1);
			}
		}
	}
}
int main() {
	char s[128], mapped[128] = {};
	mapped['N'] = 0;
	mapped['E'] = 1;
	mapped['S'] = 2;
	mapped['W'] = 3;
	while(scanf("%d %d", &n, &m) == 2 && n + m) {
		memset(g, 0, sizeof(g));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				scanf("%s", s);
				if(s[0] != 'x') {
					for(int k = 0; s[k]; k++)
						g[i][j][mapped[s[k]]] = 1;
				}
				if(s[0] == 'x')
					kind[i][j] = 0;
				else {
					int len = strlen(s);
					if(len == 4)
						kind[i][j] = 0;
					else if(len == 1 || len == 3)
						kind[i][j] = 4;
					else {
						if(g[i][j][0] == g[i][j][2])
							kind[i][j] = 2;
						else
							kind[i][j] = 4;
					}
				}
			}
		}
		solvable = 0;
		dfs(0, 0);
		puts(solvable ? "SOLVABLE" : "UNSOLVABLE");
	}
	return 0;
}
