#include <stdio.h>
#define max(x, y) ((x)<(y)?(x):(y))
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int dp[105][105] = {}, s[105];
        for(i = 0; i < n; i++)
            scanf("%d", &s[i]);
        for(j = 1; j <= n; j++) {
            for(i = 0; i < n; i++) {
                for(k = 1; k < j; k++) {
                    dp[i][j] = max(dp[i][j],
                        dp[i][k] + dp[(i+k)%n][j-k] + s[i]*s[(i+k)%n]*s[(i+j)%n]);
                }
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++)
            ans = max(ans, dp[i][n]);
        printf("%d\n", ans);
    }
    return 0;
}
