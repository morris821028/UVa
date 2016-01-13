#include <bits/stdc++.h>
using namespace std;

#define MAXN 1024
char g[2][MAXN];
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		scanf("%s%s", g[0], g[1]);

		int ret = 0;
		int A[2][MAXN] = {}, B[2][MAXN] = {};
		int used[MAXN] = {};
		int gid = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] != '.') 
					continue;
				int x = j, cnt = 0;
				while (x < n && g[i][x] == '.')
					x++, cnt++;
				x = j;
				gid++, ret++;
				while (x < n && g[i][x] == '.')
					A[i][x] = gid, B[i][x] = cnt, x++;
				j = x;
			}
		}
		
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < n; j++)
//				printf("%d", A[i][j]);
//			puts("");
//		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] != '.')
					continue;
				if (B[i][j] == 1)
					continue;
				if (used[A[i][j]])
					continue;
				int x = j;
				while (x < n && g[i][x] == '.') {
					if (g[!i][x] == '.' && !used[A[!i][x]] && B[!i][x] == 1) {
						used[A[!i][x]] = 1;
						ret--;
						break;
					}
					x++;
				}
				while (x < n && g[i][x] == '.')
					x++;
				j = x;
			}
		}
		
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] != '.')
					continue;
				if (used[A[i][j]])
					continue;
				if (B[i][j] == 1) {
					if (g[!i][j] == '.' && !used[A[!i][j]] && B[!i][j] == 1) {
						used[A[!i][j]] = 1;
						ret--;
					}
				}
			}
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}

