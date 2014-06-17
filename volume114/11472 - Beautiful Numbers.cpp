#include <stdio.h>
#include <string.h>
#define MOD 1000000007
int dp[105][1024][10];
int main() {
    int T, n, m, i, j, k;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &m);
        memset(dp[0], 0, sizeof(dp[0]));
        memset(dp[1], 0, sizeof(dp[1]));
        for(i = 1; i < n; i++)
            dp[1][1<<i][i] = 1;
        int mx = 1<<n;
        int ans = 0;
        for(i = 1; i <= m; i++) {
            memset(dp[i+1], 0, sizeof(dp[i+1]));
            for(j = 0; j < mx; j++) {
                for(k = 0; k < n; k++) {
                    if(k) {
                        dp[i+1][j|(1<<(k-1))][k-1] += dp[i][j][k];
                        if(dp[i+1][j|(1<<(k-1))][k-1] >= MOD)
                            dp[i+1][j|(1<<(k-1))][k-1] -= MOD;
                    }
                    if(k != n-1) {
                        dp[i+1][j|(1<<(k+1))][k+1] += dp[i][j][k];
                        if(dp[i+1][j|(1<<(k+1))][k+1] >= MOD)
                            dp[i+1][j|(1<<(k+1))][k+1] -= MOD;
                    }
                }
            }
            for(j = 0; j < n; j++) {
                ans += dp[i][mx-1][j];
                if(ans >= MOD)
                    ans -= MOD;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
