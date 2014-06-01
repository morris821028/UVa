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
long long getM(long long n) {
	long long l = 0, r = 3037000499LL/2, m, ret;
	long long tmp;
	while(l <= r) {
		m = (l + r) / 2;
		tmp = 4 * (m) * (m + 1);
		if(tmp <= n)
			l = m + 1, ret = m;
		else
			r = m - 1;
	}
	return ret;
}
int main() {
	unsigned long long n;
	long long inv3 = inv(3, MOD);
	while(scanf("%llu", &n) == 1 && n) {
		long long ret = 0;/*
		for(long long i = 1; i <= n; i += 2) {
			// printf("%d\n", (int)sqrt(i));
			ret += (long long) sqrt(i);
			ret %= MOD;
		}
		printf("%lld\n", ret);*/
		unsigned long long m = getM(n);
		long long prev = 4*(m)*(m + 1)%MOD*(2*m + 1)%MOD*inv3%MOD - m * (m + 1)%MOD;
		unsigned long long pn = 4 * (m) * (m + 1) - 1;
		prev = (prev%MOD + MOD)%MOD;
		//printf("%lld %lld %lld\n", m, prev, pn);
		m++;
		if(pn + m * 4 < n) {
			prev += (2 * m - 1) * 2 * m%MOD;
			pn += m * 4;
			//printf("CROSS1 %llu %llu\n", pn, prev);
			prev += (n - pn)/2 * 2 * m%MOD;
			//printf("CROSS2 %llu %llu\n", m * 2, (n - pn) /2);
		} else {
			prev += (n - pn)/2 * (2 * m - 1)%MOD;
			//puts("CROSS3");
		}
		printf("%llu\n", (prev%MOD + MOD)%MOD);
	}
	return 0;
}
/*
11
22
3333
4444
555555
666666
77777777
...
*/
/*
10000000001
*/
