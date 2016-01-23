#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
const long long MOD = 1000007;
long long dp[MAXN][MAXN];
int A[MAXN], used[MAXN];
int main() {
	dp[0][0] = dp[1][1] = 1;
	for (int i = 2; i < MAXN; i++) {
		for (int j = 1; j <= i; j++)
			dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] * (i-1))%MOD;
	}
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		int a = n, b = 0;
		memset(used, 0, sizeof(used));
		for (int i = 1; i <= n; i++) {
			if (used[i])
				continue;
			int x = i, cnt = 0;
			while (x && used[x] == 0)
				used[x] = 1, x = A[x], cnt++;
			a -= cnt-1;
			if (x == i)	m--;
			if (x == 0)	b++;
		}
		if (m < 0)
			puts("0");
		else
			printf("%lld\n", dp[b][m]);
	}
	return 0;
}
