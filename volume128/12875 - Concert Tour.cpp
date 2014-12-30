#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 128
#define MAXM 64
long long dp[MAXN][MAXM];
int profit[MAXN][MAXM], cost[MAXN][MAXN];
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &profit[i][j]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &cost[i][j]);
				
		memset(dp, 0, sizeof(dp));
		
		long long ret = 0;
		for (int i = 0; i < n; i++)
			dp[i][0] = profit[i][0];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					dp[k][i+1] = max(dp[k][i+1], dp[j][i] + profit[k][i+1] - cost[j][k]);
				}
			}
		}
		for (int i = 0; i < n; i++)
			ret = max(ret, dp[i][m-1]);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3 4
1 3 20 40
50 20 1 2
20 50 50 1
0 10 10
10 0 10
10 10 0
3 3
20 20 20
20 20 20
20 20 20
0 20 40
20 0 40
40 10 0
2 4
10 20 10 20
20 10 20 10
0 5
5 0
*/
