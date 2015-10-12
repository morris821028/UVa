#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int A[64], dp[64] = {};
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < n; i++) {
			dp[i+1] = max(dp[i+1], dp[i] + A[i]);
			dp[i+2] = max(dp[i+2], dp[i] + A[i]*2);
		}
		printf("%d\n", max(dp[n], dp[n+1]));
	}
	return 0;
}
