#include <stdio.h>
#include <math.h>
#define MOD 1000000009LL
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
int main() {
	long long inv2 = inv(2, MOD);
    long long n;
    while(scanf("%lld", &n) == 1) {
        long long ret = 0, hret = 0;
    	long long half = (long long)sqrt(n)/5;
    	long long u = -1, v = 0;
        for(half = 1; u != v; half++, u = v, v = n/half) {
        	hret += n%half;
        }
        hret -= n%(half - 1);
        hret %= MOD;
        long long l = half - 1, r, div;
        long long a0, d, tn, buff;
        while(l <= n) {
            div = n / l;
            r = n / div;
            a0 = n % l, d = -div, tn = r - l + 1;
            if(tn >= MOD)	tn %= MOD;
            if(d >= MOD)	d %= MOD;
            if(a0 >= MOD)	a0 %= MOD;
            buff = (a0 * 2 + (tn - 1)*d);
            if(buff < 0 || buff >= MOD)	buff %= MOD;
            buff *= tn;
            if(buff < 0 || buff >= MOD)	buff %= MOD;
            ret += buff;
            l = r + 1;
        }
        ret %= MOD;
        ret = (ret * inv2)%MOD;
        ret = (ret + hret + MOD)%MOD;
        printf("%lld\n", ret);
    }
    return 0;
}
/*
100000000000000
*/

