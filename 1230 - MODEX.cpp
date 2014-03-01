#include <stdio.h>
long long Mod(long long x, long long y, long long m) {
    long long ans = 1, tmp = x;
    while(y) {
        if(y&1) {
            ans *= tmp;
            ans %= m;
        }
        tmp = tmp*tmp, tmp %= m;
        y >>= 1;
    }
    return ans;
}
int main() {
    int t, x, y, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &x, &y, &n);
        printf("%lld\n", Mod(x, y, n));
    }
    return 0;
}
