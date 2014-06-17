#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int dp[1005] = {}, r, d, p, lmax;
        int i, j;
        for(i = 1; i <= n; i++)
            dp[i] = 0xfffffff;
        for(i = 0; i < n; i++) {
            scanf("%d %d %d", &r, &d, &p);
            for(j = i; j >= 0; j--) {
                lmax = dp[j]+1 > r ? dp[j]+1 : r;
                if(lmax+p-1 <= d && dp[j+1] > lmax+p-1)
                    dp[j+1] = lmax+p-1;
            }
        }
        for(i = n; i >= 0; i--)
            if(dp[i] != 0xfffffff)  break;
        printf("%d\n", i);
    }
    return 0;
}
