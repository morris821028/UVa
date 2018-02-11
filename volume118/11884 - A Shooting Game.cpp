#include <bits/stdc++.h>
using namespace std;
const int MAXN = 7;
int b[MAXN], h[MAXN], n;
double dp[MAXN*MAXN*MAXN*MAXN*MAXN*MAXN];
static inline int f(int h[]) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		ret += h[i] * b[i];
	return ret;
}
double dfs(int h[]) {
	int u = f(h);
	if (u == 0)	return 0.0f;
	double &ret = dp[u];
	if (ret >= 0)
		return ret;
	int row = 0;
	for (int i = 0; i < n; i++)
		row = max(row, h[i]);
	int hh[MAXN];
	for (int i = 1; i <= row; i++) {
		double tmp = 0;
		for (int j = 1; j <= 3; j++) {
			for (int k = 0, shot = j; k < n; k++) {
				if (shot > 0 && h[k] >= i)
					hh[k] = h[k]-1, shot--;
				else
					hh[k] = h[k];
			}
			tmp += 1 - dfs(hh);
		}
		if (tmp > ret)	ret = tmp;
		tmp = 0;
		for (int j = 1; j <= 3; j++) {
			for (int k = n-1, shot = j; k >= 0; k--) {
				if (shot > 0 && h[k] >= i)
					hh[k] = h[k]-1, shot--;
				else
					hh[k] = h[k];
			}
			tmp += 1 - dfs(hh);
		}
		if (tmp > ret)	ret = tmp;
	}
	ret /= 3;
	return ret;
}
int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &h[i]);
		b[0] = 1;
		for (int i = 1; i < n; i++) 
			b[i] = b[i-1]*(h[i-1]+1);
		fill(dp, dp+sizeof(dp)/sizeof(dp[0]), -1);
		double ret = dfs(h);
		printf("%.6lf\n", ret);
	}
	return 0;
}
/*
3
2  1  1
0
*/
