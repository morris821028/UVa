#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct vec {
    int x, y;
};
bool cmp(vec a, vec b) {
    return b.x*a.y > b.y*a.x;
}
int main() {
    int t, cases = 0, n, m;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        vec V[55];
        int sumh = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &V[i].x, &V[i].y);
            sumh += V[i].y;
        }
        sort(V, V+n, cmp);
        int dp[m+1][sumh+1], dph[m+1];
        memset(dp, 0, sizeof(dp));
        memset(dph, 0, sizeof(dph));
        dp[0][0] = 1;
        int ans = 0;
        for(i = 0; i < n; i++) {
            for(j = min(m-1, i); j >= 0; j--) {
                for(k = min(dph[j], sumh-V[i].y); k >= 0; k--) {
                    if(dp[j][k]) {
                        dp[j+1][k+V[i].y] = max(dp[j+1][k+V[i].y], dp[j][k]+(2*k+V[i].y)*V[i].x);
                        dph[j+1] = max(dph[j+1], k+V[i].y);
                    }
                }
            }
        }
        for(i = 0; i <= sumh; i++)
            ans = max(ans, dp[m][i]);
        printf("Case %d: %d\n", ++cases, ans-1);
    }
    return 0;
}
