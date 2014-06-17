#include <stdio.h>
#include <algorithm>
using namespace std;
short dp[105][105][105][40];//[length][k][tail]
short g[105][105][40];
int main() {
    int i, j, k, p, q;
    dp[0][0][0][0] = 1;
    for(i = 0; i <= 100; i++) {
        for(j = 0; j <= i; j++) {
            for(k = 0; k <= i; k++) {
                for(p = 0; p < 40; p++) {
                    g[i][j][p] += dp[i][j][k][p];
                    if(g[i][j][p] >= 10) {
                        g[i][j][p+1] += g[i][j][p]/10;
                        g[i][j][p] %= 10;
                    }
                }
                // H
                for(p = 0; p < 40; p++) {
                    dp[i+1][max(j, k+1)][k+1][p] += dp[i][j][k][p];
                    if(dp[i+1][max(j, k+1)][k+1][p] >= 10) {
                        dp[i+1][max(j, k+1)][k+1][p+1] += dp[i+1][max(j, k+1)][k+1][p]/10;
                        dp[i+1][max(j, k+1)][k+1][p] %= 10;
                    }
                }
                // T
                for(p = 0; p < 40; p++) {
                    dp[i+1][j][0][p] += dp[i][j][k][p];
                    if(dp[i+1][j][0][p] >= 10) {
                        dp[i+1][j][0][p+1] += dp[i+1][j][0][p]/10;
                        dp[i+1][j][0][p] %= 10;
                    }
                }
            }
        }
    }
    /*for(i = 0; i <= 100; i++) {
        for(j = 0; j <= i; j++) {
            for(k = 0; k <= i; k++) {
                g[i][j] += dp[i][j][k];
                // H
                dp[i+1][max(j, k+1)][k+1]
                    += dp[i][j][k];
                // T
                dp[i+1][j][0]
                    += dp[i][j][k];
            }
        }
    }
    for(i = 0; i <= 100; i++)
        for(j = i; j >= 0; j--)
            g[i][j] += g[i][j+1];*/
    for(i = 0; i <= 100; i++) {
        for(j = i; j >= 0; j--) {
            for(p = 0; p < 40; p++) {
                g[i][j][p] += g[i][j+1][p];
                if(g[i][j][p] >= 10) {
                    g[i][j][p+1] += g[i][j][p]/10;
                    g[i][j][p] %= 10;
                }
            }
        }
    }
    while(scanf("%d %d", &i, &j) == 2) {
        p = 39;
        while(g[i][j][p] == 0)  p--;
        while(p >= 0) {
            printf("%d", g[i][j][p]);
            p--;
        }
        puts("");
    }
    return 0;
}
