#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
#define eps 1e-8
int main() {
	int n, m;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		double x[50], y[50];
		double g[50][50];
		double dp[50];
		int used[50] = {};
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x[i], &y[i]);
			dp[i] = 1e+6;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				double d = hypot(x[i] - x[j], y[i] - y[j]);
				g[i][j] = d;
			}
		}
		dp[n-1] = 0;
		for (int i = 0; i < n; i++) {
			int u = -1;
			for (int j = 0; j < n; j++) {
				if (used[j] == 0 && (u == -1 || dp[u] > dp[j]))
					u = j;
			}
			used[u] = 1;
			for (int j = 0; j < n; j++) {
				if (used[j])	continue;
				double w = g[u][j];
				if (m >= dp[u] + 2 * w)
					dp[j] = min(dp[j], dp[u] + w);
				else if (m >= 3 * w) {
					int times = ceil((dp[u] - (m - 2 * w))/ (m - 3 * w));
					dp[j] = min(dp[j], dp[u] + times * (2 * w) + w);
				}
			}
		}
		printf("Trial %d: ", ++cases);
		if (dp[0] != 1e+6)
			printf("%.0lf units of food\n", ceil(dp[0]));
		else
			puts("Impossible");
		puts("");
	}
	return 0;
}
/*
4 100
10 -20
-10 5
30 15
15 35
2 100
0 0
100 100
0 0
*/
