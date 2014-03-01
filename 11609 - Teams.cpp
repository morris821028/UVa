#include <stdio.h>
#define MOD 1000000007
long long mpow(long long x, long long y, long long mod) {
    long long r = 1, z = x;
    while(y) {
        if(y&1)
            r = r*z, r %= mod;
        y >>= 1;
        z = z*z, z %= mod;
    }
    return r;
}
int main() {
    int t, cases = 0, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        long long tmp = mpow(2, n-1, MOD);
        tmp = tmp*n;
        tmp %= MOD;
        printf("Case #%d: %lld\n", ++cases, tmp);
    }
    return 0;
}
/*
C(n,1)*(C(n-1,0)+C(n-1,1)+...+C(n-1,n-1))
= n*(2^(n-1))
*/
