#include <stdio.h> 
#include <string.h>
#include <algorithm> 
using namespace std;

int g[1024][1024] = {}, w[1024][1024] = {};
int dp[1024][1024] = {}, sdp[1024][1024] = {};
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= i; j++) {
				scanf("%d", &g[i][j]);
				g[i][j] += g[i-1][j];
			}
		}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= i; j++)
				w[i][j] = g[i][j] + w[i-1][j-1];
		int ret = 0;
		memset(dp, 0, sizeof(dp));
		for(int j = 1; j <= n; j++) {
			for(int i = j; i <= n; i++) {
				dp[i][j] = w[i][j];
//				for(int k = i-1; k <= n; k++)
//					dp[i][j] = max(dp[i][j], dp[k][j-1] + g[i][j]);
				dp[i][j] = max(dp[i][j], sdp[i-1][j-1] + g[i][j]);
				ret = max(ret, dp[i][j]);
			}
			sdp[n][j] = dp[n][j];
			for(int i = n - 1; i >= j; i--)
				sdp[i][j] = max(sdp[i+1][j], dp[i][j]);
		}
		printf("%d\n", ret);
	} 
	return 0;
}
