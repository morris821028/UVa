#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;

int main() {
	int n, A[256];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		int dp[256][256];
		memset(dp, 63, sizeof(dp));
		dp[0][0] = 0;
		for(int i = 1; i <= n; i++) {
			int sum = 0;
			for(int j = i; j <= n; j++) {
				sum += A[j];
				for(int k = 1; k <= n; k++) {
					dp[j][k] = min(dp[j][k], dp[i-1][k-1] + sum * (k + j));
				}
			}
		}
		int ret = 0x3f3f3f3f;
		for(int i = 0; i <= n; i++)
			ret = min(ret, dp[n][i]);
		printf("%d\n", ret);
	}
	return 0;
}
