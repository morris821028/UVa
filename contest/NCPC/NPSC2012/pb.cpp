#include <stdio.h>

int main() {
    int t, y, I, z;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        long long dp[501][51] = {};
        dp[0][0] = 1;
        scanf("%d %d %d", &y, &I, &z);
        for(i = 1; i <= z; i++) {
            for(j = i; j <= y; j++) {
                for(k = 1; k <= I; k++) {
                    dp[j][k] += dp[j-i][k-1];
                }
            }
        }
        printf("%lld\n", dp[y][I]);
    }
    return 0;
}
