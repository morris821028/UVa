#include <stdio.h>

int main() {
    int t, n, m, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &m, &n);
        int dp[20000] = {}, mx, x;
        dp[0] = 1, mx = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            mx += x;
            if(mx > 20000)  mx = 19999;
            for(j = mx; j >= x; j--) {
                if(dp[j] == 0 || dp[j] > dp[j-x]+1) {
                    if(dp[j-x]) {
                        dp[j] = dp[j-x]+1;
                    }
                }
            }
        }
        while(dp[m] == 0)   m++;
        printf("%d %d\n", m, dp[m]-1);
    }
    return 0;
}
