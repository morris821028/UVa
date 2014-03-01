#include <stdio.h>
#include <string.h>
int p[100005];
long long dp2[100005], dp[100005], son[100005];
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 1; i < n; i++)
            scanf("%d", &p[i]);
        memset(dp, 0, sizeof(dp));
        memset(son, 0, sizeof(son));
        for(i = n-1; i > 0; i--) {
            son[i]++;
            dp[p[i]] += dp[i]+son[i];
            son[p[i]] += son[i];
        }
        for(i = 1; i < n; i++)
            dp2[i] = (dp2[p[i]]+n-son[i])+(dp[p[i]]-dp[i])-son[i];
        long long ans = dp[0]+dp2[0];
        int flag = 0;
        for(i = 0; i < n; i++) {
            if(dp[i]+dp2[i] < ans)
                ans = dp[i]+dp2[i], flag = i;
        }
        printf("%d\n", flag);
    }
    return 0;
}
