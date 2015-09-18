#include <bits/stdc++.h> 
using namespace std;
int main() {
	int dp[100005], N;
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1, f = 1; f <= 1e+5; i++, f *= i) {
		for (int j = f; j <= 1e+5; j++)
			dp[j] = min(dp[j], dp[j-f]+1);
	}
	while (scanf("%d", &N) == 1)
		printf("%d\n", dp[N]);
	return 0;
}
