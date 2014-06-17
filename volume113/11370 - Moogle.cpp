#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

double dp[205][205], w[205][205], x[205];
int main() {
	int testcase;
	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			scanf("%lf", &x[i]);
		for(i = 0; i < n; i++) {
			for(j = i+1; j < n; j++) {
				double c = 0;
				for(k = i+1; k < j; k++)
					c += fabs(x[i] + (x[j] - x[i])*(k - i)/(double)(j - i) - x[k]);
				w[i][j] = c;
			}
		}
		for(i = 0; i <= n; i++)
			for(j = 0; j <= m; j++)
				dp[i][j] = 1e+30;
		dp[0][1] = 0;
		for(i = 0; i < n; i++) {
			for(j = 1; j <= m; j++) {
				for(k = i+1; k <= n; k++) {
					dp[k][j+1] = min(dp[k][j+1], dp[i][j] + w[i][k]);
				}
			}
		}
		printf("%.4lf\n", dp[n-1][m]/n);
	}
	return 0;
}
