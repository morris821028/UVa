#include <stdio.h>
#include <string.h>
int n, dp[64][64];
char s[64];
int dfs(int l, int r) {
	if(l > r)	return 1;
	if(dp[l][r] != -1)	return dp[l][r];
	
	int &ret = dp[l][r];
	ret = 0;
	if((r - l + 1)%3)	return ret;
	
	int red, a, b, c;
	for(int i = l+1; i <= r; i++) {
		for(int j = i+1; j <= r; j++) {
			red = 0;
			red = (s[l] == 'R') + (s[i] == 'R') + (s[j] == 'R');
			if(red > 1)	continue;
			
			a = dfs(l+1, i-1);
			b = dfs(i+1, j-1);
			c = dfs(j+1, r);
			
//			printf("[%d %d] [%d %d] [%d %d] [%d %d] %d %d %d\n", l, r, (l+1)%n, (i-1)%n,
//					(i+1)%n, (j-1)%n, (j+1)%n, (r)%n, a, b, c);
			ret += a * b * c;
		}
	}
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %s", &n, s);
		memset(dp, -1, sizeof(dp));
		printf("Case %d: %d\n", ++cases, dfs(0, n-1));
	}
	return 0;
}
/*
3

6

RBBBRB
*/
