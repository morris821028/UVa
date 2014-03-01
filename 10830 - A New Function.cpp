#include <stdio.h>

int main() {
    long long n, i;
    int cases = 0;
    while(scanf("%lld", &n) == 1 && n) {
        long long ans = 0, r = n, l, m;
        //long long sum = 0;
        while(r > 1) {
            m = n/r;
            l = n/(m+1)+1;
            ans += m*(r-l+1)*(r+l)/2;
            r = l-1;
        }
        /*for(i = 2; i <= n; i++) {
            sum += i*(n/i);
        }*/
        printf("Case %d: %lld\n", ++cases, ans - n*(n+1)/2+1);
    }
    return 0;
}
