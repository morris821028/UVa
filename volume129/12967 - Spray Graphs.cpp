#include <bits/stdc++.h>
using namespace std;

int main() {
	long long dp[32] = {0, 1, 4, 12, 28};
	for (int n = 5; n <= 30; n++)
		dp[n] = dp[n-1]*2 + 4;
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%lld\n", dp[n]);
	}
	return 0;
}

