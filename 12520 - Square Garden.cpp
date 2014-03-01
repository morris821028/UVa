#include <stdio.h>

int main() {
    long long L, N;
    while(scanf("%lld %lld", &L, &N) == 2 && L) {
        long long g = L*L/2 + L%2;
        if(N <= g) {
            printf("%lld\n", N*4);
        } else {
            if(L&1) {
                long long tN = N, ans1 = g*4, ans2 = 4*(g-1);
                N -= g;
                if(N >= 4*(L/2)) {
                    ans1 -= 2*4*(L/2);
                    N -= 4*(L/2);
                } else {
                    ans1 -= N*2;
                    N = 0;
                }
                ans1 -= N*4;
                tN -= g-1;
                if(tN > 4)   tN -= 4;
                else    tN = 0;
                if(tN >= 4*(L/2-1)) {
                    ans2 -= 2*4*(L/2-1);
                    N -= 4*(L/2-1);
                } else {
                    ans2 -= tN*2;
                    tN = 0;
                }
                ans2 -= tN*4;
                printf("%lld\n", ans1 > ans2 ? ans1 : ans2);
            } else {
                long long ans = g*4;
                N -= g;
                if(N > 2)  N -= 2;
                else    N = 0;
                if(N >= 4*(L/2-1)) {
                    ans -= 2*4*(L/2-1);
                    N -= 4*(L/2-1);
                } else {
                    ans -= N*2;
                    N = 0;
                }
                ans -= N*4;
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
