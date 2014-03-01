#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    scanf("%*d");
    long long dp[105] = {};
    int i, j;
    for(i = 0;i < 105; i++)
        dp[i] = 1LL<<60;
    dp[2] = 1, dp[3] = 7;
    dp[4] = 4, dp[5] = 2;
    dp[6] = 6, dp[7] = 8;
    int cost[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    for(i = 2; i < 105; i++) {
        for(j = 0; j < 10; j++) {
            if(i+cost[j] < 105) {
                dp[i+cost[j]] = min(dp[i+cost[j]], dp[i]*10+j);
            }
        }
    }
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%lld ", dp[n]);
        if(n%2)
            putchar('7'), n -= 3;
        for(i = n/2-1; i >= 0; i--)
            putchar('1');
        puts("");
    }
    return 0;
}
