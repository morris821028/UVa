#include <stdio.h>
#include <string.h>
long long dp[55][55];
int main() {
    int i, j, k, N, K, M;
    while(scanf("%d %d %d", &N, &K, &M) == 3) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(i = 1; i <= K; i++) {
            for(j = 1; j <= N; j++) {
                for(k = 1; k <= M; k++) {
                    if(j-k >= 0)
                        dp[i][j] += dp[i-1][j-k];
                }
            }
        }
        printf("%lld\n", dp[K][N]);
    }
    return 0;
}
