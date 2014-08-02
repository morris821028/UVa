#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	unsigned long long n;
	unsigned long long dp[30][2] = {};
	unsigned long long sum[30] = {};
	dp[0][0] = 1; // [1-9^3], dp[i][1] - [3(0-9)*]
	for(int i = 1; i < 30; i++) {
		for(int j = 0; j < 2; j++) {
			dp[i][0] = 8 * dp[i-1][0] + 7 * dp[i-1][1];
			dp[i][1] = dp[i-1][0] + dp[i-1][1];
		}
	}
	for(int i = 1; i < 30; i++)
		sum[i] = sum[i-1] + (dp[i-1][0] + dp[i-1][1])* 7 + dp[i][1] - dp[i-1][1];
	while(scanf("%llu", &n) == 1) {
		int len = 0;
		for(len = 1; sum[len] <= n; len++);
		int prev = 0;
		n -= sum[len-1];
		for(int i = len; i >= 1; i--) {
			int last = -1;
			for(int j = (i == len); j <= 9; j++) {
				if(j == 4 || (prev == 1 && j == 3))	continue;
				if(j == 1) { // [1] - [0-9^3]
					if(n > dp[i-1][0]) {
						n -= dp[i-1][0], last = j;
//						printf("%llu test\n", dp[i-1][0]);
					} else {
						break;
					}
				} else {
					if(n > dp[i-1][0] + dp[i-1][1]) {
						n -= dp[i-1][0] + dp[i-1][1], last = j;
//						printf("%llu test\n", dp[i-1][0] + dp[i-1][1]);
					} else
						break;
				}
			}
			last++;
			if(last == 4)	last++;
			if(i == len && last == 0)	last = 1;
			if(prev == 1 && last == 3)	last = 5;
			printf("%d", last), prev = last;
		}
		puts("");
	}
	return 0;
}
/*
1
2
3
4
5
6
7
8
9
10
11 
12
13
14
15

*/
