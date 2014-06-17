#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
char x[505], y[505];
int dp[505][505] = {}, i, j, lx, ly;
void sol() {
    for(i = 1; i <= lx; i++)
        dp[i][0] = i;
    for(i = 1; i <= ly; i++)
        dp[0][i] = i;
    for(i = 1; i <= lx; i++) {
        for(j = 1; j <= ly; j++) {
            if(x[i-1] == y[j-1])
                dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]))+1;
            }
        }
    }
    printf("%d\n", dp[lx][ly]);
}
int main() {
    while(scanf("%d %s", &lx, x) == 2) {
        scanf("%d %s", &ly, y);
        sol();
    }
    return 0;
}
