#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int n, a[10005];
	long long dp[2][10005];
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j + i < n; j++) {
				if((i&1) == 1)
					dp[0][j] = max(dp[1][j+1] + a[j], dp[1][j] + a[j+i]);
				else
					dp[1][j] = min(dp[0][j+1], dp[0][j]);
			}
		}
		printf("%lld\n", dp[0][0]);
	}
	return 0;
}
