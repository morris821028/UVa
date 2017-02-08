// Algorithm: O(n^3)
// Online Judge: http://www.tcgs.tc.edu.tw:1218/ShowProblem?problemid=h147
// Optimization Strategy: adjust the search order to provide more cut
#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int BASE = 500*500;
static short g[MAXN][MAXN];
static short R[MAXN*MAXN*2];
static int U[MAXN*MAXN*2];
int main() {
	static int n, m, cases = 0;
	int testcase;
	scanf("%d", &testcase);
//	testcase = 1;
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			char s[MAXN];
			scanf("%s", s+1);
			for (int j = 1; j <= m; j++)
				g[i][j] = g[i-1][j] + s[j] - 'B';
		}
		
		//
		int ret = 0;
		for (int i = n-1; i >= 0; i--) {
			for (int j = 1; i+j <= n; j++) {
				if (ret >= m * (i+1))
					continue;
				++cases;
				U[0+BASE] = cases, R[0+BASE] = 0;
				int l = j, r = i+j;
				for (int k = 1, p = BASE; k <= m; k++) {
					p += g[r][k] - g[l-1][k];
					if (U[p] == cases) {
						ret = max(ret, (i+1)*(k-R[p]));
						if (ret >= m * (i+1))
							break;
					} else {
						U[p] = cases, R[p] = k;
						if (p == BASE)
							ret = max(ret, i+1);
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
