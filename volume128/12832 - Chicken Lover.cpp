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
void simplify(long long &x, long long &y) {
	long long g = gcd(x, y);
	x /= g, y /= g;
}
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long a = 0, b = 1, x, y;
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &y, &x);
			simplify(x, y);
			long long ta, tb = lcm(b, y);
			ta = a * (tb / b) + x * (tb / y);
			a = ta, b = tb;
			simplify(a, b);
		}
		printf("Case %d: %lld/%lld\n", ++cases, a, b);
	}
	return 0;
}
