#include <stdio.h>
#include <algorithm>
using namespace std;
long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
long long lcm(long long x, long long y) {
	return x / gcd(x, y) * y;
}
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long ret = 1, x;
		for (int i = 0; i < n; i++)
			scanf("%lld", &x), ret = lcm(ret, x);
		printf("Case %d: %lld\n", ++cases, ret * (5+10+20));
	}
	return 0;
}
/*
2
3
4 5 6
4
10 14 15 35
*/
