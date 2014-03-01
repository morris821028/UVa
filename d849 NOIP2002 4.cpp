#include <stdio.h>
#include <string.h>
int g[30][30] = {};
int n, m, x, y;
void color(int x, int y) {
    if(x < 0 || y < 0 || x > n || y > m)
        return ;
    g[x][y] = 1;
}
int main() {
    while(scanf("%d %d %d %d", &n, &m, &x, &y) == 4) {
        memset(g, 0, sizeof(g));
        color(x, y);
        color(x+2, y+1);
        color(x+2, y-1);
        color(x+1, y+2);
        color(x+1, y-2);
        color(x-2, y+1);
        color(x-2, y-1);
        color(x-1, y+2);
        color(x-1, y-2);
        long long dp[30][30] = {}, i, j;
        dp[0][0] = 1;
        for(i = 0; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                if(g[i][j] == 0) {
                    if(i-1 >= 0)
                        dp[i][j] += dp[i-1][j];
                    if(j-1 >= 0)
                        dp[i][j] += dp[i][j-1];
                }
            }
        }
        printf("%lld\n", dp[n][m]);
    }
    return 0;
}
