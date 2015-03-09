#include <stdio.h>
#include <string.h>
long long dp[101][101] = {}, w[101] = {};
long long dfs(int i, int j) {
    if(dp[i][j] != -1)
        return dp[i][j];
    long long min = 0xfffffffffffffffLL, tmp;
    int k;
    for(k = i; k <= j; k++) {
        tmp = dfs(i, k-1) + dfs(k+1, j) + (w[j]-w[k]-w[k-1]+w[i-1])*(w[j]-w[k]-w[k-1]+w[i-1]);
        if(tmp < min)
            min = tmp;
    }
    dp[i][j] = min;
    return dp[i][j];
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        memset(dp, -1, sizeof(dp));
        for(i = 1; i <= n; i++) {
            scanf("%lld", &w[i]);
            w[i] += w[i-1];
            dp[i][i] = 0;
            dp[i][i-1] = 0;
        }
        printf("%lld\n", dfs(1, n));
    }
    return 0;
}
