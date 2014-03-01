#include <stdio.h>
char dp[1000005];
int main() {
    int n, m, s[15], i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < m; i++)
            scanf("%d", &s[i]);
        dp[0] = 0;
        for(i = 1; i <= n; i++) {
            dp[i] = 0;
            for(j = 0; j < m; j++) {
                if(i-s[j] >= 0) {
                    if(dp[i-s[j]] == 0) {
                        dp[i] = 1;
                        break;
                    }
                }
            }
        }
        if(dp[n])
            puts("Stan wins");
        else
            puts("Ollie wins");
    }
    return 0;
}
