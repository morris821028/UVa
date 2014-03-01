#include <stdio.h>

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        int dp1[10205] = {}, dp2[10205] = {};
        int i, j, p, f, ans = 0;
        dp1[0] = 1, dp2[0] = 1;
        for(i = 0; i < m; i++) {
            scanf("%d %d", &p, &f);
            for(j = n-p; j >= 0; j--) {
                if(dp1[j+p] < dp1[j]+f && dp1[j])
                    dp1[j+p] = dp1[j]+f;
            }
            for(j = n-p+200; j >= 0; j--) {
                if(dp2[j+p] < dp2[j]+f && dp2[j])
                    dp2[j+p] = dp2[j]+f;
            }
        }
        for(i = 0; i <= n; i++)
            ans = ans > dp1[i] ? ans : dp1[i];
        for(i = n > 1800 ? 2001 : n+201; i <= n+200; i++)
            ans = ans > dp2[i] ? ans : dp2[i];
        printf("%d\n", ans-1);
    }
    return 0;
}
