#include <stdio.h>
#define LL long long

int main() {
    int t;
    LL n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        m = 1;
        int cnt = 0;
        while(m <= n)
            n -= m, m *= 2, cnt++;
        while(m) {
            while(n >= m)
                n -= m, cnt++;
            m /= 2;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
