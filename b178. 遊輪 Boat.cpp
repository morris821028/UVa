#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int a, b;
} Te;
Te B[1000];
int cmp(const void *i, const void *j) {
    static Te *a, *b;
    a = (Te *)i, b = (Te *)j;
    return a->a - b->a;
}
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &B[i].a, &B[i].b);
        qsort(B, n, sizeof(Te), cmp);
        int ans = 0;
        for(k = 0; k < n; k++) {
            if(n-k < ans)   break;
            int dp[1000] = {};
            dp[k] = 1;
            for(i = k; i < n; i++) {
                if(dp[i])
                for(j = i+1; j < n; j++) {
                    if(B[j].a < B[k].b && B[j].b > B[i].b && dp[i]+1 > dp[j]) {
                        dp[j] = dp[i]+1;
                    }
                    if(B[j].a > B[k].b) break;
                }
                if(dp[i] > ans) ans = dp[i];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
