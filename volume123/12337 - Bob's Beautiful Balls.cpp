#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int check(int n, int m, int len, char s[]) {
	const int dx[] = {0, 1, 0, -1};
	const int dy[] = {1, 0, -1, 0};
	int dir = 0, x = 0, y = 0;
	int visited[128][128] = {};
	char g[128][128] = {};
	for(int i = 0; i < len; i++) {
		visited[x][y] = 1, g[x][y] = s[i];
		int ok = 0, tx, ty;
		tx = x + dx[dir], ty = y + dy[dir];
		if(tx >= 0 && tx < n && ty >= 0 && ty < m && visited[tx][ty] == 0)
			ok = 1, x = tx, y = ty;
		if(!ok) {
			dir = (dir + 1)%4;
			tx = x + dx[dir], ty = y + dy[dir];
			x = tx, y = ty;
		}
	}
//	for(int i = 0; i < n; i++, puts("")) {
//		for(int j = 0; j < m; j++)
//			printf(
//			"%c", g[i][j]);
//	}
//	puts("--");
	int ret = 1;
	for(int i = 0; i < m && ret; i++) {
		int f = 1;
		for(int j = 1; j < n; j++)
			f &= g[j-1][i] == g[j][i];
		ret &= f;
	}
	return ret;
}
int main() {
	int testcase, cases = 0, N;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		N = strlen(s);
		int ret = 0x3f3f3f3f;
		for(int i = 2; i < N; i++) {
			if(N%i == 0) {
				if(check(i, N/i, N, s))
					ret = min(ret, i + N / i);
			}
		}
		printf("Case %d: %d\n", ++cases, ret == 0x3f3f3f3f ? -1 : ret);
	}
	return 0;
}
/*
3
BGWBBGGGBBWGBBGWBB
GBBWBBWBBB
BBBBBBBBBBBBBBB
*/
