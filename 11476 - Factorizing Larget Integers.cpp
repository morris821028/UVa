#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LL long long
#define maxL (100000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL], pt = 0;
LL p[6000000];
void sieve() {
    register int i, j, k;
    int n = 100000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            p[pt++] = i;
        }
    }
}
LL powLL(LL x, LL n, LL mod) {
    LL Ans = 1, t = x;
    while(n) {
        if(n&1)
            Ans *= t, Ans %= mod;
        t *= t, t %= mod, n >>= 1;
    }
    return Ans;
}
int isprime(LL n) {
    if(n == 2 || n == 3)    return 1;
    if(n == 1)    return 0;
    if(!(n&1))    return 0;
    static int i, flag;
    static LL t, x;
    flag = 1;
    for(i = 0; i < 10; i++) {
        x = rand()%(n-4)+2;
        t = powLL(x, n-1, n);
        if(t != 1)    return 0;
    }
    return 1;
}
void sol(LL n) {
    static int i, j, cnt;
    printf("%lld =", n);
    if(isprime(n)) {
        printf(" %lld\n", n);
        return ;
    }
    for(i = 0, j = 0; i < pt && p[i]*p[i] <= n; i++) {
        if(n%p[i] == 0) {
            cnt = 1;
            n /= p[i];
            while(n%p[i] == 0)
                n /= p[i], cnt++;
            if(j)   printf(" *");
            printf(" %lld", p[i]);
            if(cnt != 1)
                printf("^%d", cnt);
            j++;
            if(isprime(n))
                break;
        }
    }
    if(n != 1) {
        if(j)   printf(" *");
        printf(" %lld", n);
    }
    puts("");
}
main() {
    sieve();
    int t;
    LL n;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        sol(n);
    }
    return 0;
}
