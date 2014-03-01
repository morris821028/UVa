#include <stdio.h>

int main() {
    int t, n, i, j;
    int A[100];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sum = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]), sum += A[i];
        int hsum = sum/2, hn = n/2;
        long long dp[hsum+1];
        for(i = 0; i <= hsum; i++)
            dp[i] = 0;
        dp[0] = 1;
        for(i = 0; i < n; i++) {
            for(j = hsum; j >= A[i]; j--)
                dp[j] |= dp[j-A[i]]<<1LL;
        }
        if(n%2)
            while(!(dp[hsum]&(1LL<<hn)) && !(dp[hsum]&(1LL<<(hn+1))))
                hsum--;
        else
            while(!(dp[hsum]&(1LL<<hn)))
                hsum--;

        printf("%d %d\n", hsum, sum-hsum);
        if(t)
            puts("");
    }
    return 0;
}
