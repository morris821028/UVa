#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
int A[MAXN], dp[MAXN][2], n;
// dp, O(n^2)
// dp + greedy, O(n)
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		dp[1][0] = dp[1][1] = 1;
		for (int i = 2; i <= n; i++) {
			if (A[i] == A[i-1]) {
				dp[i][0] = dp[i-1][0];
				dp[i][1] = dp[i-1][1];
			} else if (A[i] > A[i-1]) {
				dp[i][1] = max(dp[i-1][0]+1, dp[i-1][1]);
				dp[i][0] = dp[i-1][0];
			} else {
				dp[i][0] = max(dp[i-1][1]+1, dp[i-1][0]);
				dp[i][1] = dp[i-1][1];
			}
		}
		printf("%d\n", max(dp[n][0], dp[n][1]));
	}
	return 0;
}

