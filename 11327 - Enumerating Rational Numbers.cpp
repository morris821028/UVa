#include <stdio.h>
int p[5500], pt = 0;
long long gcd(long long x, long long y) {
    long long t;
    while(x%y) {
        t = x, x = y, y = t%y;
    }
    return y;
}
void sieve() {
    char mark[32767] = {};
    int i, j;
    for(i = 2; i < 32767; i++)
        if(!mark[i]) {
            p[pt++] = i;
            for(j = i+i; j < 32767; j += i)
                mark[j] = 1;
        }
}
int sol(int n) {
    static int a, b, i;
    a = 1, b = n;
    for(i = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            a *= p[i]-1;
            b /= p[i];
            n /= p[i];
            while(n%p[i] == 0)
                n /= p[i];
        }
    }
    if(n != 1)
        a *= n-1, b /= n;
    return a*b;
}
long long dp[210001] = {1,2};
int main() {
    long long n;
    sieve();
    int i;
    for(i = 2; i <= 210000; i++)
        dp[i] = dp[i-1] + sol(i);
    while(scanf("%lld", &n) == 1 && n) {
        int l = 0, r = 210000, m;
        while(l < r) {
            m = (l+r)/2;
            if(dp[m] < n)
                l = m+1;
            else
                r = m;
        }
        long long k;
        if(r)
            k = n - dp[r-1];
        else
            k = n;
        if(r == 0) {
            puts("0/1");
            continue;
        }
        if(r == 1) {
            puts("1/1");
            continue;
        }
        for(i = 0; ; i++) {
            if(gcd(i, r) == 1)
                k--;
            if(k == 0)  break;
        }
        printf("%d/%d\n", i, r);
    }
    return 0;
}
