#include <stdio.h>
#include <assert.h>
const long long mod = 1000000007LL;
long long mul(long long a, long long b) {
	long long ret = 0;
	for( ; b != 0 ; b>>=1, (a<<=1)%=mod)
		if(b&1)
			(ret += a) %= mod;
	return ret;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1LL, x = (x * x)%mod;
	}
	return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int testcase, cases = 0;
	long long D, V;
	scanf("%d", &testcase);
	while (scanf("%lld %lld", &D, &V) == 2) {
		assert(D >= 0 && V > 0 && D <= 2e+9 && V <= 2e+9);
		long long ret = 0;
		if (D == 0)			ret = 1;
		else if (D == 1)	ret = (V + 1)%mod;
		else if (V == 1)	ret = -1;
		else if (V == 2)	ret = (1 + D * 2)%mod;
		else {
			ret = mpow(V - 1, D, mod) - 1 + mod;
			ret = ret * mpow(V - 2, mod - 2, mod) %mod;
			ret = ret * V %mod;
			ret = (ret + 1 + mod)%mod;
			assert(ret >= 0);
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
1000
0 1
1 2
1 5
500 1
0 500
2000000000 2000000000
*/
