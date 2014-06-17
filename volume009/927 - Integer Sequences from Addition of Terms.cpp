#include <stdio.h>
long long mypow(long long x, long long y) {
    if(y == 0)  return 1;
    if(y&1)
        return x*mypow(x*x, y/2);
    else
        return mypow(x*x, y/2);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, d, k, i, j;
        scanf("%d", &n);
        long long c[30];
        for(i = 0; i <= n; i++)
            scanf("%lld", &c[i]);
        scanf("%d %d", &d, &k);
        int tk = 0, tb = 0;
        for(i = 1; ; i++) {
            long long an = 0;
            for(j = 0; j <= n; j++)
                an += c[j]*mypow(i, j);
            tb += d;
            tk += tb;
            if(tk >= k) {
                printf("%lld\n", an);
                break;
            }
        }
    }
    return 0;
}
