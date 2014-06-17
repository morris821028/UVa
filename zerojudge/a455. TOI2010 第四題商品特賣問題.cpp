#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <functional>
using namespace std;
char p[1000][3000];
int main() {
    int m, n, i, j, k;
    int C[1005], W[1005];
    while(scanf("%d %d", &m, &n) == 2) {
        for(i = 0; i < m; i++)
            scanf("%d", &C[i]);
        for(i = 0; i < n; i++)
            scanf("%d", &W[i]);
        sort(C, C+m);
        sort(W, W+n, greater<int>());
        int used[1000] = {};
        int ans = 0;
        for(i = 0; i < m; i++) {
            int dp[3000] = {};
            int mx = 0, tmpN;
            memset(p, 0, sizeof(p));
            dp[0] = 0;
            for(j = 0; j < n; j++) {
                if(used[j] == 0) {
                    for(k = C[i]; k >= 0; k--) {
                        if(k-W[j] >= 0 && dp[k-W[j]]+1 > dp[k]) {
                            dp[k] = dp[k-W[j]]+1;
                            p[j][k] = 1;
                        }
                    }
                }
            }
            mx = dp[C[i]];
            if(mx == 0) break;
            ans += mx;
            for(j = n-1, k = C[i]; j >= 0; j--) {
                if(p[j][k]) {
                    used[j] = 1;
                    k -= W[j];
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
