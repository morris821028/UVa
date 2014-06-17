#include <stdio.h>
#include <string.h>
int main() {
    int t, G, K, R;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &G, &K, &R);
        int dp[2][10001] = {};
        int flag = 0;
        dp[flag][0] = 1;
        int i, j, gi;
        for(i = 0; i < G; i++) {
            scanf("%d", &gi);
            gi %= 1000000007;
            for(j = 0; j < K; j++) {
                dp[1-flag][j] = dp[flag][(j+gi)%K]+dp[flag][((j-gi)%K+K)%K];
                dp[1-flag][j] %= 1000000007;
            }
            flag = 1-flag;
        }
        printf("%d\n", dp[flag][R]);
    }
    return 0;
}
