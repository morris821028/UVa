#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int n, m, q, r;
	int g[105][105], mg[15][15];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
				
		scanf("%d %d", &q, &r);
		for(int i = 0; i < q; i++)
			for(int j = 0; j < r; j++)
				scanf("%d", &mg[i][j]);
				
		int cx = q / 2, cy = r / 2;
		int ret[105][105] = {};
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				ret[i][j] |= g[i][j];
				if(g[i][j] == 0)	continue;
				int ox = i - cx, oy = j - cy;
				for(int a = 0; a < q; a++) {
					for(int b = 0; b < r; b++) {
						if(ox + a < 0 || ox + a >= n)
							continue;
						if(oy + b < 0 || oy + b >= m)
							continue;
						ret[ox + a][oy + b] |= mg[a][b];
					}
				}
			}
		}
		printf("Case %d:\n", ++cases);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				printf("%d%c", ret[i][j], j == m - 1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}
/*
2
3 4
0 0 0 0
0 1 1 0
0 0 0 0
3 3
0 1 0
1 1 1
0 1 0
4 4
0 0 0 0
0 1 0 0
0 0 1 0
0 0 0 0
3 3
1 1 1
1 1 1
1 1 1
*/
