#include <stdio.h>
#define LL long long
void gcd(LL x, LL y, LL k) {
    LL t;
    LL flag = 1, la = 1, lb = 0, ra = 0, rb = 1;
    while(x%y) {
        if(flag) {
            la -= (x/y)*ra;
            lb -= (x/y)*rb;
        } else {
            ra -= (x/y)*la;
            rb -= (x/y)*lb;
        }
        t = x, x = y, y = t%y;
        flag = 1-flag;
    }
    if(!flag)    printf("%lld %lld\n", la*k/y, lb*k/y);
    else        printf("%lld %lld\n", ra*k/y, rb*k/y);
}
int main() {
    LL x, k;
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld %lld", &x, &k);
        LL a, b;
        a = x/k, b = x/k + (x%k != 0);
        gcd(a, b, x);
    }
    return 0;
}
