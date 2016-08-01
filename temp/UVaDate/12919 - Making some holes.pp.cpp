#include <stdio.h>
#include <algorithm>
using namespace std;

long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, d;
		scanf("%d %d", &n, &d);
		long long x, ret = 1;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			x -= d;
			ret = ret / gcd(ret, x) * x;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1
3 4
8 23 12
*/
