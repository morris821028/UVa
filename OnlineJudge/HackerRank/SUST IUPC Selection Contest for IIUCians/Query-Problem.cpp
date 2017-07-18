#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
const int MAXN = 131072;
const int64_t MOD = 1000000007;
static int64_t A[MAXN];
static int64_t S[MAXN], P[MAXN];
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int n, q;
        scanf("%d %d", &n, &q);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &A[i]);
        for (int i = 1; i <= n; i++) {
            S[i] = (S[i-1] + A[i])%MOD;
            P[i] = (P[i-1] + i*A[i])%MOD;
        }
        
        
        printf("Case %d:\n", ++cases);
        for (int i = 0; i < q; i++) {
            int64_t l, r, k;
            scanf("%lld %lld %lld", &l, &r, &k);
            
            int64_t ret = 0;
            ret += P[r] - P[l-1], ret %= MOD;
            ret += (k-l)*(S[r] - S[l-1]), ret %= MOD;
            ret = (ret + MOD)%MOD;
            printf("%lld\n", ret);
        }
    }
    return 0;
}
