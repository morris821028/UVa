#include <bits/stdc++.h>
using namespace std;
const int MOD = 10000;
int mpow(int x, int y, int MOD) {
	int32_t ret = 1;
	x %= MOD;
	while (y) {
		if (y&1)
			ret = (ret*x)%MOD;
		y >>= 1, x = (x*x)%MOD;
	}
	return ret;
}
int digits(int x) {
	if (x == 0)	return 1;
	int ret = 0;
	while (x)
		x /= 10, ret++;
	return ret;
}
int main() {
	int A[20] = {};	//
	for (int i = 1, d = 1; i < 20; i++) {
		A[i] = (A[i-1] + d*9*i%MOD)%MOD;
		d = d*10%MOD;
	}
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		int d = digits(n);
		int ret = 0;
		int base = mpow(10, d-1, MOD);
		ret += (4LL*n-2)%MOD;						// `()+x` except for coefficient
		ret += (A[d-1] + (n-base+1)%MOD*d%MOD - 1);	// exponent number
		ret += mpow(2, n, MOD)-(n+1)%MOD;			// `a`
		ret += mpow(2, n-1, MOD)*(A[d-1] + (n-base+1)%MOD*d%MOD)%MOD;	//
		ret += mpow(2, n-1, MOD)*(n%MOD)%MOD;	//
		ret = (ret%MOD + MOD)%MOD;
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
