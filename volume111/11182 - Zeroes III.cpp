#include <bits/stdc++.h>
using namespace std;
// O(n) 
long long dp[1048576] = {};
long long count(int n, int p) {
	long long ret = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i/p] + i/p;
		ret += (long long) dp[i] * (n-i+1);
	}
	return ret;
}
// O(log n)
long long f2(int n, int p) {
	long long ret = 0, tp = p, cnt = 1;
	while (n >= tp) {
		for (int i = 1; n - tp*i+1 > 0; i++) {
			if (i%p == 0)
				continue;
			long long st = n - tp*i + 1, ed = 1;
			ret += (st + ed) * (st-ed+1)/2 * cnt;
		}
		tp *= p;
		cnt ++;
	}
	return ret;
}
int main() {
	int n, b;
	while (scanf("%d %d", &n, &b) == 2 && n) {
		int mxp = 1;
		long long ret = LONG_LONG_MAX;
		for (int i = 2; i <= b; i++) {
			if (b%i == 0) {
				mxp = i;
				int cnt = 0;
				while (b%i == 0)
					b /= i, cnt++;
//				printf("A:%lld\nB:%lld\n", count(n, i), f2(n, i));
//				ret = min(ret, count(n, i)/cnt);
				ret = min(ret, f2(n, i)/cnt);
			}
		}
		
		printf("%lld\n", ret);
	}
	return 0;
}
