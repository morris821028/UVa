#include <stdio.h>

int main() {
    int N, m;
    while(scanf("%d %d", &N, &m) == 2) {
        int v[65], p[65], q[65], att[65][2] = {};
        int i, j;
        for(i = 1; i <= m; i++) {
            scanf("%d %d %d", &v[i], &p[i], &q[i]);
            if(q[i]) {
                if(att[q[i]][0])
                    att[q[i]][1] = i;
                else
                    att[q[i]][0] = i;
            }
        }
        int dp[32005] = {}, ans = 0;
        for(i = 1; i <= m; i++) {
            if(q[i] == 0)
            for(j = N; j >= 0; j--) {
                int mx = 0;
                if(j-v[i] >= 0 && mx < dp[j-v[i]]+v[i]*p[i])
                    mx = dp[j-v[i]]+v[i]*p[i];
                if(att[i][0]) {
                    if(j-v[i]-v[att[i][0]] >= 0 && mx <
                       dp[j-v[i]-v[att[i][0]]]+v[i]*p[i]+v[att[i][0]]*p[att[i][0]])
                       mx = dp[j-v[i]-v[att[i][0]]]+v[i]*p[i]+v[att[i][0]]*p[att[i][0]];
                }
                if(att[i][1]) {
                    if(j-v[i]-v[att[i][1]] >= 0 && mx <
                       dp[j-v[i]-v[att[i][1]]]+v[i]*p[i]+v[att[i][1]]*p[att[i][1]])
                       mx = dp[j-v[i]-v[att[i][1]]]+v[i]*p[i]+v[att[i][1]]*p[att[i][1]];
                    if(j-v[i]-v[att[i][0]]-v[att[i][1]] >= 0 && mx <
                       dp[j-v[i]-v[att[i][0]]-v[att[i][1]]]+v[i]*p[i]+v[att[i][0]]*p[att[i][0]]+v[att[i][1]]*p[att[i][1]])
                       mx = dp[j-v[i]-v[att[i][0]]-v[att[i][1]]]+v[i]*p[i]+v[att[i][0]]*p[att[i][0]]+v[att[i][1]]*p[att[i][1]];
                }
                if(dp[j] < mx)  dp[j] = mx;
            }
        }
        for(i = 0; i <= N; i++)
            if(ans < dp[i])
                ans = dp[i];
        printf("%d\n", ans);
    }
    return 0;
}
