#include <stdio.h>
#define maxN 90000
int main() {
    int n, w[maxN], p[maxN], dp[maxN][2], i; /*0 no 1 yes*/
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%d", &w[i]);
            dp[i][0] = dp[i][1] = 0;
        }
        for(i = 1; i < n; i++)
            scanf("%d", &p[i]);
        for(i = n-1; i >= 0; i--) {
            dp[i][1] += w[i];
            if(i) {
                dp[p[i]][0] += (dp[i][0] > dp[i][1] ? dp[i][0] : dp[i][1]);
                dp[p[i]][1] += dp[i][0];
            }
        }
        printf("%d\n", dp[0][0] > dp[0][1] ? dp[0][0] : dp[0][1]);
    }
    return 0;
}
