#include <stdio.h> 
#include <string.h>
#include <algorithm> 
using namespace std;

int g[512][512], w[512][512];
int main() {
	int testcase, cases = 0;
	int n, m, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				g[i][j] = w[i][j] = 0xf3f3f3f;
		while(m--) {
			scanf("%d %d", &x, &y);
			w[x][y] = w[y][x] = g[x][y] = g[y][x] = 1;
		}
		int ret = 0xf3f3f3f;
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(i != j)
						ret = min(ret, w[k][i] + g[i][j] + w[j][k]);
				}
			}
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
		printf("Case %d: ", ++cases);
		if(ret == 0xf3f3f3f)
			puts("impossible");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
3
3 3
0 1
1 2
2 0
2 1
0 1
5 6
0 1
1 2
1 3
2 3
0 4
3 4
*/
