#include <stdio.h>
#define mod 1000000007LL
int main() {
    int testcase;
    int cases, n, i, j;
    long long pi, ai, ans;
    scanf("%d", &testcase);
    cases = 0;
    while(testcase--) {
        scanf("%d", &n);
        ans = 1;
        long long N = 1;
        for(i = 0; i < n; i++) {
            scanf("%lld %lld", &pi, &ai);
            long long tmp = 1, sum = 0;
            for(j = 0; j < ai; j++) {
                sum += tmp;
                sum %= mod;
                tmp = tmp*pi;
                tmp %= mod;
            }
            N *= tmp;
            N %= mod;
            tmp = tmp*(ai+1);
            tmp %= mod;
            sum = (sum+tmp)%mod;
            ans *= sum;
            ans %= mod;
        }
        printf("Case %d: %lld\n", ++cases, (ans+N)%mod);
    }
    return 0;
}
