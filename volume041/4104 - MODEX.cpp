#include <stdio.h>
long long mod(long long x, long long y, long long n) {
    long long ans = 1, tmp = x;
    while(y) {
        if(y&1)
            ans *= tmp, ans %= n;
        tmp = tmp*tmp;
        tmp %= n;
        y /= 2;
    }
    return ans;
}
int main() {
    int t, x, y, n;
    while(scanf("%d", &t) == 1 && t) {
        while(t--) {
            scanf("%d %d %d", &x, &y, &n);
            printf("%lld\n", mod(x, y, n));
        }
    }
    return 0;
}
