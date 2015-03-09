#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;
long long dp[2005][2005];
long long A[2005];
int main() {
	int testcase, n;
	int i, j;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		long long ML[2005], MR[2005];
		for(i = 0; i < n; i++)
			ML[i] = MR[i] = -(1e+15);
		int l, r;
		for(i = 0; i < n; i++) {
			for(j = 0; j + i < n; j++) {
				l = j, r = j + i;
				dp[l][r] = max(A[l], A[r]);
				dp[l][r] = max(max(ML[r], MR[l]), dp[l][r]);
				if(l -1  >= 0)
					ML[r] = max(ML[r], A[l-1] - dp[l][r]);
				if(r + 1 < n)
					MR[l] = max(MR[l], A[r+1] - dp[l][r]);
			}
		}
		printf("%lld\n", dp[0][n-1]);
	}
	return 0;
}
