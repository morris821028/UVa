#include <stdio.h>

int main() {
    int i, j;
    unsigned long long dp[101][64], n, k;
    for(i = 1; i <= 100; i++) {
        for(j = 1; j < 64; j++) {
            if(j == 1)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i-1][j-1]+dp[i][j-1]+1;
        }
    }
    while(scanf("%llu %llu", &k, &n) == 2 && k) {
        for(i = 1; i < 64; i++) {
            if(dp[k][i] >= n)
                break;
        }
        if(i > 63)
            puts("More than 63 trials needed.");
        else
            printf("%d\n", i);
    }
    return 0;
}
