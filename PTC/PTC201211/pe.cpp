#include <stdio.h>
#include <algorithm>
#define oo 2147483647
using namespace std;
int coin[1005];
int dp[1005][1005];
int dfs(int l, int r, int k) {
    if(dp[l][r] != -oo)
        return dp[l][r];
    if(l > r)   return 0;
    int i, j, sum = 0;
    for(i = l, j = 0; i <= r && j < k; i++, j++) {
        sum += coin[i];
        dp[l][r] = max(dp[l][r], sum - dfs(i+1, r, k));
    }
    return dp[l][r];
}
int main() {
    int n, k, i, j;
    while(scanf("%d %d", &n, &k) == 2) {
        for(i = 1; i <= n; i++)
            scanf("%d", &coin[i]);
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                dp[i][j] = -oo;
            }
            dp[i][i] = coin[i];
        }
        dfs(1, n, k);
        printf("%d\n", dp[1][n]);
    }
    return 0;
}
