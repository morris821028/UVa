#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long dp[2][2][25];
long long ans[130][130][25];
int alen[130][130];
void sol(int n, int m) {
    memset(dp, 0, sizeof(dp));
    int i, j, k, roll = 1;
    int p, q;
    int dplen[2][2] = {};
    dp[1][0][0] = m-2; // none one tail
    dp[1][1][0] = 1; // one tail
    ans[m][1][0] = m-1;
#define base 100000000000LL
    for(i = 1; i < n;) {
        memset(dp[1-roll], 0, sizeof(dp[0]));
        memset(dplen[1-roll], 0, sizeof(dplen[0]));

        for(p = 0; p <= dplen[roll][0]; p++)
            dp[1-roll][1][p] = dp[roll][0][p];
        dplen[1-roll][1] = dplen[roll][0];
        for(p = 0; p <= dplen[roll][1]; p++)
            dp[1-roll][1][p] += dp[roll][1][p];
        dplen[1-roll][1] = max(dplen[1-roll][0], dplen[roll][1]);
        dplen[1-roll][1] += 5;
        for(p = 0; p <= dplen[1-roll][1]; p++) {
            if(dp[1-roll][1][p] >= base) {
                dp[1-roll][1][p+1] += dp[1-roll][1][p]/base;
                dp[1-roll][1][p] %= base;
            }
        }
        while(dplen[1-roll][1] > 0 && dp[1-roll][1][dplen[1-roll][1]] == 0)
            dplen[1-roll][1]--;

        for(p = 0; p <= dplen[roll][0]; p++)
            dp[1-roll][0][p] = dp[roll][0][p]*(m-1);
        dplen[1-roll][0] = dplen[roll][0];
        for(p = 0; p <= dplen[roll][1]; p++)
            dp[1-roll][0][p] += dp[roll][1][p]*(m-2);
        dplen[1-roll][0] = max(dplen[1-roll][0], dplen[roll][1]);
        dplen[1-roll][0] += 5;
        for(p = 0; p <= dplen[1-roll][0]; p++) {
            if(dp[1-roll][0][p] >= base) {
                dp[1-roll][0][p+1] += dp[1-roll][0][p]/base;
                dp[1-roll][0][p] %= base;
            }
        }
        while(dplen[1-roll][0] > 0 && dp[1-roll][0][dplen[1-roll][0]] == 0)
            dplen[1-roll][0]--;

        roll = 1-roll;
        i++;
        alen[m][i] = max(dplen[roll][0], dplen[roll][1]);
        for(q = 0; q <= alen[m][i]; q++)
            ans[m][i][q] = dp[roll][0][q]+dp[roll][1][q];
        alen[m][i] += 5;
        for(q = 0; q <= alen[m][i]; q++) {
            if(ans[m][i][q] >= base) {
                ans[m][i][q+1] += ans[m][i][q]/base;
                ans[m][i][q] %= base;
            }
        }
        while(alen[m][i] > 0 && ans[m][i][alen[m][i]] == 0)
            alen[m][i]--;
    }
}
int main() {
    int n, m, i;
    for(m = 4; m <= 128; m++)
        sol(100, m);
    while(scanf("%d %d", &m, &n) == 2) {
        if(m == 0)  break;
        printf("%lld", ans[m][n][alen[m][n]]);
        for(i = alen[m][n]-1; i >= 0; i--)
            printf("%011lld", ans[m][n][i]);
        puts("");
    }
    return 0;
}
