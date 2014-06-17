#include <stdio.h>
#include <math.h>
int dp[5000] = {}, from[5000];
int dsum[5000] = {};
int build(int n) {
    if(dp[n])   return dp[n];
    int i, j, nt = 0, sq = (int)sqrt(n);
    for(i = 1; i <= sq; i++) {
        if(n%i == 0) {
            nt += dsum[i];
            if(n/i != i)
                nt += dsum[n/i];
        }
    }
    if(nt == n) dp[n] = 1;
    else dp[n] = build(nt)+1;
    from[n] = nt;
    return dp[n];
}
int main() {
    int i, m, n, cases = 0;
    for(i = 0; i <= 3000; i++) {
        m = i;
        dsum[i] = dsum[i/10] + i%10;
    }
    for(i = 0; i <= 3000; i++)
        build(i);
    while(scanf("%d %d", &m, &n) == 2) {
        printf("Input%d: %d %d\n", ++cases, m, n);
        if(m > n)   i = m, m = n, n = i;
        int mx = 0, mn;
        for(i = m; i <= n; i++) {
            if(dp[i] > mx)
                mx = dp[i], mn = i;
        }
        printf("Output%d:", cases);
        while(1) {
            printf(" %d", mn);
            if(dp[mn] == 1) break;
            mn = from[mn];
        }
        puts("");
    }
    return 0;
}
