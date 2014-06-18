#include <stdio.h>
#include <string.h>
int g[10][10], n, m;
int n5[100000][10];
void build5num() {
    int i, j;
    for(i = 0; i < 100000; i++) {
        n5[i][0] = i;
        for(j = 0; j < 9; j++) {
            n5[i][j+1] = n5[i][j]/5;
            n5[i][j] %= 5;
        }
    }
}
int sol() {
    int i, j, k, l;
    int s5 = 1;
    for(i = 1; i <= m; i++)
        s5 *= 5;
    int dp[2][s5], roll = 0;
    int buf[10], x, p;
    memset(dp[0], 0, sizeof(dp));
    dp[0][0] = 1;
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++) {
            memset(dp[1-roll], 0, sizeof(dp[0]));
            for(k = 0; k < s5; k++) {
                if(dp[roll][k] == 0)
                    continue;
                if(g[i][j]) {
                    memcpy(buf, n5[k], sizeof(buf));
                    buf[j-1] = 0;
                    x = 0;
                    for(p = m-1; p >= 0; p--)
                        x = x*5 + buf[p];
                    dp[1-roll][x] = dp[1-roll][x] + dp[roll][k];
                    if(dp[1-roll][x] >= 1000000007)
                        dp[1-roll][x] -= 1000000007;
                } else {
                    memcpy(buf, n5[k], sizeof(buf));
                    for(l = 1; l <= 4; l++) {
                        if(n5[k][j-1] != l && (j == 1 || n5[k][j-2] != l)) {
                            buf[j-1] = l;
                            x = 0;
                            for(p = m-1; p >= 0; p--)
                                x = x*5 + buf[p];
                            dp[1-roll][x] = dp[1-roll][x] + dp[roll][k];
                            if(dp[1-roll][x] >= 1000000007)
                                dp[1-roll][x] -= 1000000007;
                        }
                    }
                }
            }
            roll = 1-roll;
        }
    }
    int ans = 0;
    for(i = 0; i < s5; i++) {
        ans += dp[roll][i];
        if(ans >= 1000000007)
            ans -= 1000000007;
    }
    return ans;
}
int main() {
    build5num();
    int t, x, y, k;
    int cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        scanf("%d", &k);
        memset(g, 0, sizeof(g));
        while(k--) {
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
        }
        n++, m++;
        printf("Case %d: %d\n", ++cases, sol());
    }
    return 0;
}
