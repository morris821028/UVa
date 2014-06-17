#include <stdio.h>
long long Mod(long long x, long long y, long long m) {
    long long ans = 1, tmp = x;
    while(y) {
        if(y&1) {
            ans *= tmp;
            ans %= m;
        }
        y >>= 1;
        tmp *= tmp, tmp %= m;
    }
    return ans;
}
int isPrime(int x) {
    int i;
    for(i = 2; i*i <= x; i++)
        if(x%i == 0)
            return 0;
    return 1;
}
int main() {
    long long p, a;
    while(scanf("%lld %lld", &p, &a) == 2) {
        if(p == 0 && a == 0)
            break;
        if(isPrime(p) || Mod(a, p, p) != a)
            puts("no");
        else
            puts("yes");
    }
    return 0;
}
