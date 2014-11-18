#include <stdio.h> 
#include <math.h>
#include <algorithm> 
using namespace std;
#define MAXN 256
double dp[MAXN][MAXN], dist[MAXN][MAXN];
int used[MAXN][MAXN];
double dfs(int l, int r) {
	if (used[l][r])	return dp[l][r];
	if (r - l <= 3)	return 0;
	used[l][r] = 1;
	double &ret = dp[l][r];
	ret = 1e+30;
	for (int i = l + 1; i <= r - 1; i += 2) {
		for (int j = i + 1; j <= r- 1; j += 2) {
			ret = min(ret, dfs(l, i) + dfs(i, j) + dfs(j, r) + 
							dist[l][i] + dist[i][j] + dist[j][r]);
		}
	}
	return ret;
}
int main() {
	int n;
	double x[MAXN], y[MAXN];
	while (scanf("%d", &n) == 1) {
		n = n * 2;
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &x[i], &y[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dist[i][j] = hypot(x[i] - x[j], y[i] - y[j]);
				used[i][j] = 0;
			}
			dist[i][i + 1] = 0;
		}
		double ret = dfs(0, n-1);
		printf("%.4lf\n", ret);
	}
	return 0;
}
/*
4
5715.7584 3278.6962
3870.5535 4086.7950
3823.2104 4080.7543
3574.4323 170.2905
4521.4796 144.9156
4984.6486 306.2896
5063.1061 347.1661
6099.9959 2095.9358
2
6044.4737 2567.9978
5752.5635 3226.5140
5148.8242 3802.9292
4598.8042 4036.8000
*/
