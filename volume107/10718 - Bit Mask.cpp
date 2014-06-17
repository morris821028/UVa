#include <stdio.h>

int main() {
    long long N, L, R, ans, l, r;
    while(scanf("%lld %lld %lld", &N, &L, &R) == 3) {
        ans = 0;
        long long i;
        for(i = 31; i >= 0; i--) {
            if(N&(1LL<<i)) {
                r = ans + (1LL<<i);
                if(r <= L)
                    ans += 1LL<<i;
            } else {
                l = ans + (1LL<<i);
                if(l <= R)
                    ans += 1LL<<i;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
