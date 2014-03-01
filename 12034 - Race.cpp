#include <stdio.h>
#define mod 10056
int dp[1005][1005], res[1005];
int main() {
    dp[0][0] = 1;
    int i, j;
    for(i = 1; i <= 1001; i++) {
        for(j = 1; j <= i; j++) {
            dp[i][j] = dp[i-1][j]*j + dp[i-1][j-1]*j;
            dp[i][j] %= mod;
            res[i] += dp[i][j];
            res[i] %= mod;
        }
    }
    scanf("%*d");
    i = 0;
    while(scanf("%d", &j) == 1)
        printf("Case %d: %d\n", ++i, res[j]);
    return 0;
}
