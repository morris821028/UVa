#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;
int main() {
    int t, n, w, u[105];
    int dp[105][105];
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &w);
        for(i = 1; i <= n; i++)
            scanf("%d", &u[i]);
        sort(u+1, u+n+1, greater<int>());
        memset(dp, 63, sizeof(dp));
        int sum[105] = {};
        for(i = 1; i <= n; i++)
            sum[i] = sum[i-1]+u[i];
        dp[0][0] = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= w; j++) {
                for(k = 0; k < i; k++) {
                    dp[i][j] = min(dp[i][j], dp[k][j-1] + i*(sum[i]-sum[k]));
                }
            }
        }
        printf("%.4lf\n", dp[n][w]/(double)sum[n]);
    }
    return 0;
}
