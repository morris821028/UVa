#include <stdio.h>
#include <string.h>
int main() {
    int w[65536], x[65536], n;
    while(scanf("%d", &n) == 1) {
        int i, j, k = 1<<n;
        for(i = 0; i < k; i++)
            scanf("%d", &w[i]);
        memset(x, 0, sizeof(x));
        for(i = 0; i < k; i++) {
            for(j = 0; j < n; j++)
                x[i] += w[i^(1<<j)];
        }
        int ans = 0;
        for(i = 0; i < k; i++) {
            for(j = 0; j < n; j++) {
                if(ans < x[i]+x[i^(1<<j)])
                    ans = x[i]+x[i^(1<<j)];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
