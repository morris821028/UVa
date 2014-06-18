#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define maxL (20000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
#define LL long long
int mark[maxL] = {};
long long p[2000000], pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 20000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            p[pt++] = i;
        }
    }
}
long long cntDivisor(long long n) {
    static long long i, j, t;
    j = 1;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            t = 1;
            n /= p[i];
            while(n%p[i] == 0)
                n /= p[i], t++;
            j *= (t+1);
        }
    }
    if(n != 1)  j *= 2;
    return j;
}
int main() {
    sieve();
    long long c;
    while(scanf("%lld", &c) == 1 && c) {
        long long n = c*4-3;
        long long cnt;
        cnt = cntDivisor(n);
        printf("%lld %lld\n", c, cnt);
    }
    return 0;
}
