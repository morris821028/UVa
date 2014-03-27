#include <stdio.h>
#define MOD 1000000009LL
int main() {
    long long n, k;
    while(scanf("%lld", &n) == 1) {
    	k = n;
        long long l = 1, r, div;
        long long ret = 0;
        while(l <= k) {
            div = k/l;
            r = k/div;
            // d = div
            if(r > n)   r = n;
            long long a0 = k%l, d = -div, tn = r-l+1;
            ret += (a0*2+(tn-1)*d)*tn/2;
            ret %= MOD;
            //printf("%lld %lld %lld\n", l, r, k%l);
            l = r+1;
            if(r == n)
                break;
        }
        if(l <= n)
            ret += (n-l+1)*k;
        ret %= MOD;
        printf("%lld\n", ret);
    }
    return 0;
};
