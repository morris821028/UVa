#include <stdio.h>
#include <algorithm>
using namespace std;

long long dp[1024] = {};
int main() {
	dp[0] = 1;
	for (int i = 1; i < 1024; i <<= 1) {
		for (int j = 1023; j >= i; j--) {
			for (int k = 1; k <= 2; k++) {
				if (j - i*k >= 0)
					dp[j] += dp[j - i*k];
			}
		}
	}
	long long ret = 0;
	for (int i = 1; i < 100; i++) {
		ret = max(ret, dp[i]);
		printf("%d %lld\n", i, ret);
	}
	return 0;
}
