#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int A[255] = {}, dp[255][255], e[255];
        int i, j, k, tmp;
        for(i = 1; i <= n; i++)
            scanf("%d", &e[i]), A[i] = A[i-1]+e[i];
        for(k = 0; k < n; k++) {
            for(i = 1; i+k <= n; i++) {
                dp[i][i+k] = 0xfffffff;
                for(j = i; j <= i+k; j++) {
                    tmp = dp[i][j-1]+dp[j+1][i+k]+A[i+k]-A[i-1]-e[j];
                    if(tmp < dp[i][i+k])
                        dp[i][i+k] = tmp;
                }
            }
        }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}
