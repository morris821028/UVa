#include <stdio.h>

const int MOD = 1000000007;
const int MAXN = 64;
long long C[MAXN][MAXN] = {};
int main() {
    C[0][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
    }
    int testcase, n;
    int A[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        
        long long dp[MAXN][MAXN] = {};
        
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i; j <= n; j++) {
                for (int k = 0; k <= A[i+1] && j+k <= n; k++) {
                    dp[i+1][j+k] += (dp[i][j] * C[A[i+1]][k])%MOD;
                    dp[i+1][j+k] %= MOD;
                }
            }
        }
        printf("%lld\n", dp[n][n]);
    }
    return 0;
}
/*
 1
 3
 2 1 2
*/