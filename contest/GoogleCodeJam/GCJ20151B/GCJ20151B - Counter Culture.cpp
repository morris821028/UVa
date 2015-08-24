#include <stdio.h>
#include <string.h>

long long reverseNumber(long long x) {
	static char buf[32];
	sprintf(buf, "%lld", x);
	
	long long y = 0;
	for (int i = strlen(buf) - 1; i >= 0; i--)
		y = y * 10 + buf[i] - '0';
	return y;
}
long long f(long long n) {
	if (n < 10)
		return n;
	long long half = 1;
	while (half * half <= n)	
		half *= 10;
	if (n % half == 0)	// 1000 -> 999, 10000 -> 9999
		return 1 + f(n - 1);
	else {				
		long long v = reverseNumber(n - n%half + 1);
		if (v != n - n%half + 1)	// 123654 -> 100321, subtract & reverse
			return n%half + f(v);
		else						// 19 -> 11, but 11 is palindrome, without reverse -> 10
			return n%half + f(v-1);
	}
}
int main() {
	int testcase, cases = 0;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		printf("Case #%d: %lld\n", ++cases, f(n));
	}
	return 0;
}
