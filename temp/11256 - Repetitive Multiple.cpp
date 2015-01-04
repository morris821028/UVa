#include <stdio.h>

long long llgcd(long long x, long long y) {
	long long t;
	while (x%y) 
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	long long t10[20];
	t10[0] = 1;
	for (int i = 1; i < 20; i++)
		t10[i] = t10[i-1] * 10;
	int testcase;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		long long ret = -1;
		for (int i = 1; i <= 9; i++) {
			long long pattern = 1;// 1010, 100100100, ...
			for (int j = i + i; j <= 18; j += i) {
				pattern = pattern * t10[i] + 1;
				long long k = n / llgcd(pattern, n);
				if (k < t10[i]) {
					long long t = (t10[i-1] + k - 1) / k * k; // result cannot like 0101, 01230123
					if (ret == -1 || ret > pattern * t) {
//						printf("%lld %lld\n", pattern, t);
						ret = pattern * t;
					}
				}
			} 
		}
		printf("%lld\n", ret);
	}
	return 0;
}
