#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int sum = 0, A[20];
		char dp[262144] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			sum += A[i];
		}
		if (sum%2) {
			puts("NO");
			continue;
		}
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = sum/2; j >= A[i]; j--)
				dp[j] |= dp[j-A[i]];
		}
		puts(dp[sum/2] ? "YES" : "NO");
	}
	return 0;
}

