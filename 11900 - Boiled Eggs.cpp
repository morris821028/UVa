#include <stdio.h>

int main() {
    scanf("%*d");
    int n, P, Q, cases = 0;
    while(scanf("%d %d %d", &n, &P, &Q) == 3) {
        int dp[35] = {}, i, j, x;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            for(j = Q; j >= x; j--) {
                if(dp[j] < dp[j-x]+1)
                    dp[j] = dp[j-x]+1;
            }
        }
        int mx = 0;
        for(i = 0; i <= Q; i++)
            if(dp[i] > mx)
                mx = dp[i];
        if(mx > P)  mx = P;
        printf("Case %d: %d\n", ++cases, mx);
    }
    return 0;
}
