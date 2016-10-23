#include <bits/stdc++.h>
using namespace std;

int main() {
	unsigned long long dp[100] = {0, 1, 1, 2, 3};
	for (int i = 2; i < 100; i++)
		dp[i] = dp[i-1] + dp[i-2];
	int n;
	while (scanf("%d", &n) == 1 && n)
		printf("%llu\n", dp[n]);
	return 0;
}

