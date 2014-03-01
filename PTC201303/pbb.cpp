#include <stdio.h>
#include <string.h>
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
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        long long a, b;
        char c[65005];
        int v[65005];
        scanf("%lld %lld %s", &a, &b, &c);
        int len = strlen(c);
        for(i = 0; c[i]; i++)
            v[i] = c[i]-'0';
        long long ans = 1, tmp2 = a;
        while(1) {
            int tmp = 0;
            for(i = st; i < len; i++) {
                tmp = tmp*10 + v[i];
                v[i] = tmp/2;
                tmp %= 2;
            }
            if(tmp) {
                ans *= tmp2;
                ans %= b;
            }
            tmp2 = tmp2*tmp2%b;
            for(; st < len; i++)
                if(v[i])
                    break;
            if(i == len)
                break;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
