#include <stdio.h>
#include <algorithm>
using namespace std;

long long dp[1048576] = {};
const long long mod = 1000000007LL;
int main() {
	dp[0] = 1, dp[1] = 2, dp[2] = 9, dp[3] = 32;
	long long c = 4;
	for(int i = 4; i <= 1000000; i++) {
		c = (c + dp[i-3] * 4)%mod; // {ZigZag}
		dp[i] = (dp[i-1] * 2 + dp[i-2] * 5 + c)%mod; 
	}
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		printf("%d\n", dp[n]);
	}
	return 0;
}
/*
1000
1
2
3
4
5
6
7

2
9
32
121
450
1681
6272
*/
