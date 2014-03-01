#include <stdio.h>
#include <string.h>
int dp[1001][1001];
int dfs(int n, int m) {
    if(dp[n][m] != -1)
        return dp[n][m];
    if(n == 1)  return 1;
    if(n == 0)  return 0;
    int &flag = dp[n][m];
    int i;
    flag = 0;
    for(i = 1; i <= m && i <= n; i++) {
        flag |= !dfs(n-i, i*2);
        if(flag)    return flag;
    }
    return flag;
}
int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    while(scanf("%d", &n) == 1 && n) {
        if(dfs(n, n-1))
            puts("Alicia");
        else
            puts("Roberto");
    }
    return 0;
}
