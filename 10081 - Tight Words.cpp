#include <stdio.h>

int main() {
    int k, n;
    while(scanf("%d %d", &k, &n) == 2) {
        double dp[101][10] = {};
        int i, j, l;
        for(i = 0; i <= k; i++)
            dp[1][i] = (double)100/(k+1);
        for(i = 1; i < n; i++) {
            for(j = 0; j <= k; j++) {
                for(l = -1; l <= 1; l++) {
                    if(j+l >= 0 && j+l <= k) {
                        dp[i+1][j+l] += dp[i][j]/(k+1);
                    }
                }
            }
        }
        double ans = 0;
        for(i = 0; i <= k; i++)
            ans += dp[n][i];
        printf("%.5lf\n", ans);
    }
    return 0;
}
