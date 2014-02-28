#include <stdio.h>
#include <string.h>

int main() {
    int n, i, j, flag, order;
    int x[20], y[20];
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d", &order);
        order--;
        x[order] = i;
    }
    while(1) {
        flag = 0;
        for(i = 0; i < n; i++) {
            if(scanf("%d", &order) != 1)
                {flag = 1;break;}
            order--;
            y[order] = i;
        }
        if(flag)    break;
        int dp[25][25] = {};
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                if(x[i-1] == y[j-1])
                    dp[i][j] = dp[i-1][j-1]+1;
                else
                    dp[i][j] = dp[i-1][j] > dp[i][j-1] ?
                        dp[i-1][j] : dp[i][j-1];
            }
        }
        printf("%d\n", dp[n][n]);
    }
    return 0;
}
