#include <stdio.h>

int main() {
    int n, m, x, i, j, k, r, cases = 0;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        int label[150] = {};
        for(i = 0; i < n; i++)
            scanf("%d", &x), label[x]++;
        printf("Case %d:\n", ++cases);
        while(m--) {
            scanf("%d", &r);
            long long dp[100][100] = {};
            dp[0][0] = 1;
            for(i = 1; i <= n; i++) {
                for(j = 0; j <= r; j++)
                    dp[i][j] = dp[i-1][j];
                for(j = 0; j <= r; j++) {
                    for(k = 1; k <= label[i] && j+k <= r; k++) {
                        dp[i][j+k] += dp[i-1][j];
                    }
                }
            }
            printf("%lld\n", dp[n][r]);
        }
    }
    return 0;
}
