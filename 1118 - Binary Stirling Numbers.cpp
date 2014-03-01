#include <stdio.h>
int main() {
    int i, j;
    char dp[200][200] = {};
    dp[0][0] = 1;
    for(i = 1; i <= 100; i++) {
        dp[i][0] = 0;
        for(j = 0; j <= i; j++) {
            if(j > 0)
                dp[i][j] = j*dp[i-1][j] + dp[i-1][j-1];
            dp[i][j] %= 2;
            printf("%d", dp[i][j]);
        }
        puts("");
    }
    return 0;
}
