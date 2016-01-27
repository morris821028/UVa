#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
void exgcd(long long x, long long y, long long &g,
		long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long inverse(long long x, long long p) {
	long long g, b, r;
	exgcd(x, p, g, r, b);
	if (g < 0)	r = -r;
	return (r%p + p)%p;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n;
		scanf("%lld", &n);
		n++;
		long long ret = 1;
		ret = (n+1)*(n)%MOD*(n-1)%MOD;
		ret = ret * inverse(2, MOD)%MOD * inverse(3, MOD)%MOD;
		ret = ret * 2 %MOD;
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

