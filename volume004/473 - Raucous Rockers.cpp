#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    int testcase;
    int n, t, m, i, j, k, x;
    scanf("%d", &testcase);
    short dp[2][100][100];
    while(testcase--) {
        scanf("%d %d %d", &n, &t, &m);
        memset(dp, 0, sizeof(dp));
        int flag = 0, ans  = 0;
        for(i = 0; i < n; i++) {
            scanf("%d%*c", &x);
            for(j = 1; j <= m; j++) {
                for(k = 0; k <= t; k++) {
                    // no record in [j] disk
                    dp[flag][j][k] = max(dp[1-flag][j][k],
                        max(dp[1-flag][j-1][t], dp[flag][j-1][t]));
                    // record in [j] disk
                    if(k >= x)
                        dp[flag][j][k] = max((int)dp[flag][j][k], dp[1-flag][j][k-x]+1);
                    if(dp[flag][j][k] > ans)
                        ans = dp[flag][j][k];
                }
            }
            flag = 1-flag;
        }
        printf("%d\n", ans);
        if(testcase)
            puts("");
    }
    return 0;
}
