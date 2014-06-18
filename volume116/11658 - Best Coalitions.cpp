#include <stdio.h>

int main() {
    int n, m, i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        int A[100], a, b;
        for(i = 0; i < n; i++) {
            scanf("%d.%d", &a, &b);
            a = a*100 + b, A[i] = a;
        }
        if(A[m-1] > 5000) {
            puts("100.00");
            continue;
        }
        int dp[10001] = {}, up = 10000-A[m-1];
        dp[0] = 1;
        for(i = 0; i < n; i++) {
            if(i == m-1)    continue;
            for(j = up-A[i]; j >= 0; j--) {
                if(dp[j])
                    dp[j+A[i]] = 1;
            }
        }
        up = 5001-A[m-1];
        while(!dp[up])  up++;
        printf("%.2lf\n", (double)A[m-1]*100/(up+A[m-1]));
    }
    return 0;
}
