#include <stdio.h>
long long dp[2005][2005];
int main() {
    int n, i, j;
    int ans[2005] = {};
    dp[1][1] = 1;
    for(i = 1; i <= 2000; i++) {
        for(j = 1; j <= i; j++) {
            ans[i] += dp[i][j];
            if(ans[i] >= 9999997)
                ans[i] -= 9999997;
            dp[i+1][j] += (dp[i][j]*j)%9999997;
            dp[i+1][j+1] += dp[i][j];
            dp[i+1][j] %= 9999997;
            dp[i+1][j+1] %= 9999997;
        }
    }
    while(scanf("%d", &n) == 1)
        printf("%d\n", ans[n]);
    return 0;
}
