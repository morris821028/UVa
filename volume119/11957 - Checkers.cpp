#include <stdio.h>

int main() {
    int t, n, i, j, cases = 0;
    char g[105][105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        int dp[105][105] = {};
        for(i = n-1; i >= 0; i--) {
            for(j = 0; j < n; j++) {
                if(g[i][j] == 'W') {
                    dp[i][j] = 1;
                    continue;
                }
                if(g[i][j] == 'B')
                    continue;
                if(i+1 < n && j+1 < n && g[i+1][j+1] != 'B')
                    dp[i][j] += dp[i+1][j+1];
                if(i+1 < n && j-1 >= 0 && g[i+1][j-1] != 'B')
                    dp[i][j] += dp[i+1][j-1];
                if(i+1 < n && j+1 < n && g[i+1][j+1] == 'B') {
                    if(i+2 < n && j+2 < n && g[i+2][j+2] != 'B')
                        dp[i][j] += dp[i+2][j+2];
                }
                if(i+1 < n && j-1 >= 0 && g[i+1][j-1] == 'B') {
                    if(i+2 < n && j-2 >= 0 && g[i+2][j-2] != 'B')
                        dp[i][j] += dp[i+2][j-2];
                }
                dp[i][j] %= 1000007;
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++)
            if(g[0][i] != 'B')
                ans += dp[0][i], ans %= 1000007;
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
