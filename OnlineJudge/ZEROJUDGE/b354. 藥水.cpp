#include <bits/stdc++.h>
using namespace std;

int main() {
	const int INF = 0x3f3f3f3f;
	int n, m[2];
	long long dp[2][10005];
	scanf("%d %d %d", &n, &m[0], &m[1]);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j <= 10000; j++)
			dp[i][j] = INF;
		dp[i][0] = 0;
		for (int j = 0; j < m[i]; j++) {
			int c, w;
			scanf("%d %d", &c, &w);
			for (int k = 10000; k >= w; k--)
				dp[i][k] = min(dp[i][k], dp[i][k-w]+c);
		}
	}
	long long c[2];
	for (int i = 0; i < 2; i++) {
		int a;
		scanf("%d", &a);
		c[i] = INF;
		for (int j = a; j <= 10000; j++)
			c[i] = min(c[i], dp[i][j]);
	}
	if (c[0] + c[1] <= n)
		printf("%lld\n", c[0] + c[1]);
	else
		puts("GG");
	return 0;
}
