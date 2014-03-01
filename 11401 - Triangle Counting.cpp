#include <stdio.h>
unsigned long long dp[1000005];
int main() {
    dp[3] = 0, dp[4] = 1;
    unsigned long long i, b;
    for(i = 5; i <= 1000000; i++) {
        b = i/2 + 1;
        dp[i] = dp[i-1] + i*(i-1)-(i+1)*(i-b) - b*(b-1);
    }
    int n;
    while(scanf("%d", &n) == 1 && n >= 3)
        printf("%llu\n", dp[n]);
    return 0;
}
