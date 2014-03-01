#include <stdio.h>

int inv(int n, int m) { // get n*? = 1 (mod m)
    int la = 1, lb = 0, ra = 0, rb = 1;
    int i = 0, t, mod = m;
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
    int cases = 0, p, e, i, d;
    // 23*28*33 = 21252
    while(scanf("%d %d %d %d", &p, &e, &i, &d) == 4) {
        if(p < 0)   break;
        int days;
        days = p*inv(28*33, 23)*28*33 + e*inv(23*33, 28)*23*33 + i*inv(23*28, 33)*23*28-d;
        days += 21251;
        days %= 21252;
        printf("Case %d: the next triple peak occurs in %d days.\n", ++cases, days+1);
    }
    return 0;
}
