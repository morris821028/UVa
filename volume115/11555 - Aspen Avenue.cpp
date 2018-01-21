#include <bits/stdc++.h> 
using namespace std;

static const int MAXN = 1024;
static double dp[MAXN][MAXN];
double interval;
const double INF = 1e+30;
int P[MAXN*2];
int L, W, n;
double dfs(int l, int r) {
	if (l == 0 && r == 0)
		return 0;
	double &ret = dp[l][r];
	if (ret < INF)
		return ret;
	if (l > 0)
		ret = min(ret, dfs(l-1, r) + fabs(P[l+r-1]-(l-1)*interval));
	if (r > 0) {
		double dx = P[l+r-1]-(r-1)*interval;
		ret = min(ret, dfs(l, r-1) + sqrt(dx*dx + W*W));
	}
	return ret;
}
int main() {
	while (scanf("%d", &n) == 1) {
		scanf("%d %d", &L, &W);
		for (int i = 0; i < n; i++)
			scanf("%d", &P[i]);
		sort(P, P+n);
		int p = 0, m = n/2;
		for (int i = 0; i <= m; i++)
			fill(dp[i], dp[i]+m+1, 1e+30);
		interval = (double) L / (m-1);
		printf("%.10lf\n", dfs(m, m));
	}
	return 0;
}
/*
4
10  1
1
0
10
10
6
10  1
0
9
3
5
5 
6
*/
