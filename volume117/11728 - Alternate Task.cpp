#include <stdio.h>

int main() {
    int dp[1005] = {};
    int S, i, j, cases = 0;
    for(i = 1; i <= 1000; i++) {
        int sum = 0;
        for(j = 1; j*j <= i; j++) {
            if(i%j == 0) {
                sum += j;
                if(j*j != i)
                    sum += i/j;
            }
        }
        if(sum <= 1000)
            dp[sum] = i;
    }
    while(scanf("%d", &S) == 1 && S) {
        printf("Case %d: %d\n", ++cases, dp[S] ? dp[S] : -1);
    }
    return 0;
}
