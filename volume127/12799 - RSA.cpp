#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;
#define MOD 100000000 
long long inv(long long n, long long m) { // get n*? = 1 (mod m)
    long long la = 1, lb = 0, ra = 0, rb = 1;
    long long i = 0, t, mod = m;
    while(n%m) {
        if(!i) {
            la -= n/m*ra;
            lb -= n/m*rb;
        } else {
            ra -= n/m*la;
            rb -= n/m*lb;
        }
        i = !i;
        t = n, n = m, m = t%m;
    }
    if(i)
        return (la%mod+mod)%mod;
    return (ra%mod+mod)%mod;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
}
int main() {
	int N, E, C;
	while (scanf("%d %d %d", &N, &E, &C) == 3) {
		int sqr = (int)sqrt(N);
		int phi = N;
		for (int i = 3; i <= sqr; i++) {
			if (N%i == 0)
				phi = (i - 1) * (N/i - 1);
		}
		int d = inv(E, phi);
		printf("%lld\n", mpow(C, d, N));
	}
	return 0;
}
/*
1073 71 436
91 43 19
*/
