#include <stdio.h>
#define MAXN 1048576
const long long mod = 1000000007LL; // prime
long long f[MAXN];
long long mul(long long a, long long b, long long mod) {
	long long ret = 0;
	for( ; b != 0; b>>=1, (a<<=1)%=mod)
		if(b&1) (ret += a) %= mod;
	return ret;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)% mod;
		x = (x * x)%mod, y >>= 1;
	}
	return ret;
}
int main() {
	f[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		f[i] = (f[i-1] * i)% mod;
//		printf("%d\n", i);
	}
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		int x, sum = 0;
		long long ret = 1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			ret = (ret * f[sum + x - 1])%mod;
			ret = (ret * mpow((f[x - 1] * f[sum])%mod, mod - 2, mod))%mod;
			sum += x;
			// ret = ret * C(sum+x-1, sum); leave one on tail
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
