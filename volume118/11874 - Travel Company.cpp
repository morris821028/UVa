#include <stdio.h> 
#include <string.h>
#include <algorithm> 
using namespace std;

int g[128][128];
int main() {
	int testcase, cases = 0;
	int n, m, p, x, y, income, expense;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &n, &m, &p);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				g[i][j] = 0xf3f3f3f;
		while(m--) {
			scanf("%d %d %d %d", &x, &y, &income, &expense);
			g[x][y] = min(g[x][y], expense * p - income);
		}
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		}
		int ret = 0;
		for(int i = 0; i < n; i++)
			ret |= g[i][i] < 0;
		printf("Case %d: %s\n", ++cases, ret ? "YES" : "NO");
	}
	return 0;
}
