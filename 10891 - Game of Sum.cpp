#include <stdio.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
char done[101][101];
int dp[101][101], A[101];
int dfs(int l, int r) {
    if(l > r)      return 0;
    if(done[l][r])  return dp[l][r];
    int i, sum;
    dp[l][r] = -(1<<30);
    done[l][r] = 1;
    for(i = l, sum = 0; i <= r; i++) {
        sum += A[i];
        dp[l][r] = max(dp[l][r], sum-dfs(i+1, r));
    }
    for(i = r, sum = 0; i >= l; i--) {
        sum += A[i];
        dp[l][r] = max(dp[l][r], sum-dfs(l, i-1));
    }
    return dp[l][r];
}
int main() {
    int n, i, j;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", A+i);
        for(i = 0; i <= n; i++)
            for(j = 0; j <= n; j++)
                done[i][j] = 0;
        printf("%d\n", dfs(0, n-1));
    }
    return 0;
}
