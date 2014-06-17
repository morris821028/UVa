#include <stdio.h>
#include <string.h>
#include <string.h>
int main() {
    int t, n, w, i, j;
    int d[30], v[30], td[30];
    int first = 0;
    while(scanf("%d %d", &t, &w) == 2) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &d[i], &v[i]);
            td[i] = 3*w*d[i];
        }
        int dp[1001] = {}, cnt[1001] = {};
        int graph[1001][30] = {};
        for(i = n-1; i >= 0; i--) {
            for(j = t; j >= td[i]; j--) {
                if(dp[j-td[i]] + v[i] > dp[j]) {
                    dp[j] = dp[j-td[i]] + v[i];
                    cnt[j] = cnt[j-td[i]] + 1;
                    graph[j][i] = 1;
                }
            }
        }
        if(first)   puts("");
        first = 1;
        printf("%d\n%d\n", dp[t], cnt[t]);
        j = t;
        for(i = 0, j = t; i < n; i++) {
            if(graph[j][i] == 1) {
                printf("%d %d\n", d[i], v[i]);
                j -= td[i];
            }
        }
    }
    return 0;
}
