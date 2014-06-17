#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[2][130][100];
int ans[130][130][100], alen[130][130];
void sol(int n, int m) {
    memset(dp, 0, sizeof(dp));
    int i, j, k, roll = 1;
    int p, q;
    int dplen[2][128] = {};
    for(i = 1; i < m; i++)
        dp[1][i][0] = 1;
    ans[m][1][0] = m-1;
#define base 10000000
    for(i = 1; i < n;) {
        memset(dp[1-roll], 0, sizeof(dp[0]));
        memset(dplen[1-roll], 0, sizeof(dplen[0]));
        for(j = 0; j < m; j++) {
            for(k = 0; k < m; k++) {
                if(j == 1 && k == 3)
                    continue;
                for(p = 0; p <= dplen[roll][j]; p++)
                    dp[1-roll][k][p] += dp[roll][j][p];
                dplen[1-roll][k] = max(dplen[1-roll][k], dplen[roll][j]);
                for(p = 0; p <= dplen[1-roll][k]; p++) {
                    if(dp[1-roll][k][p] >= base) {
                        dp[1-roll][k][p+1] += dp[1-roll][k][p]/base;
                        dp[1-roll][k][p] %= base;
                    }
                }
                dplen[1-roll][k] += 5;
                while(dplen[1-roll][k] > 0 && dp[1-roll][k][dplen[1-roll][k]] == 0)
                    dplen[1-roll][k]--;
            }
        }
        roll = 1-roll;
        i++;
        for(p = 0; p < m; p++) {
            for(q = 0; q <= dplen[roll][p]; q++)
                ans[m][i][q] += dp[roll][p][q];
            alen[m][i] = max(alen[m][i], dplen[roll][p]);
            for(q = 0; q <= alen[m][i]; q++) {
                if(ans[m][i][q] >= base) {
                    ans[m][i][q+1] += ans[m][i][q]/base;
                    ans[m][i][q] %= base;
                }
            }
            alen[m][i] += 5;
            while(alen[m][i] > 0 && ans[m][i][alen[m][i]] == 0)
                alen[m][i]--;
        }
    }
}
int main() {
    int n, m, i;
    for(m = 4; m <= 128; m++) {
        printf("%d\n", m);
        sol(100, m);
    }
    while(scanf("%d %d", &m, &n) == 2) {
        if(m == 0)  break;
        printf("%d", ans[m][n][alen[m][n]]);
        for(i = alen[m][n]-1; i >= 0; i--)
            printf("%07d", ans[m][n][i]);
        puts("");
    }
    return 0;
}
