// Algorithm: O(n^3)
// Online Judge: http://www.tcgs.tc.edu.tw:1218/ShowProblem?problemid=h147

#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int BASE = 500*500;
int main() {
	static int n, m, cases = 0;
	static char g[MAXN][MAXN];
	static short R[MAXN*MAXN*2];
	static int U[MAXN*MAXN*2];
	int testcase;
	scanf("%d", &testcase);
//	testcase = 1;
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
			
		// transfer
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				g[i][j] = g[i][j] - 'B';
		}
		
		//
		int ret = 0;
		for (int i = 0; i < n; i++) {
			short sum[MAXN] = {};
			for (int j = i; j < n; j++) {
				for (int k = 0; k < m; k++)
					sum[k] += g[j][k];
				++cases;
				U[0+BASE] = cases, R[0+BASE] = -1;
				for (int k = 0, p = BASE; k < m; k++) {
					p += sum[k];
					if (U[p] == cases) {
						ret = max(ret, (j-i+1)*(k-R[p]));
						if (ret >= m * (j-i+1))
							break;
					} else {
						U[p] = cases, R[p] = k;
						if (p == BASE)
							ret = max(ret, j-i+1);
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

