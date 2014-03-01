#include <stdio.h>
#include <string.h>
int main() {
    char s[50];
    while(scanf("%s", s) == 1) {
        long long dp[20][20] = {};
        int i, j, k, n;
        n = strlen(s);
        if(s[0] == '?') {
            for(i = 0; i < n; i++)
                dp[0][i] = 1;
        } else {
            if(s[0] <= '9')
                s[0] -= '1';
            else
                s[0] = s[0]-'A'+9;
            dp[0][s[0]] = 1;
        }
        for(i = 1; i < n; i++) {
            if(s[i] == '?') {
                for(j = 0; j < n; j++) {
                    for(k = 0; k < j-1; k++)
                        dp[i][j] += dp[i-1][k];
                    for(k = j+2; k < n; k++)
                        dp[i][j] += dp[i-1][k];
                }
            } else {
                if(s[i] <= '9')
                    s[i] -= '1';
                else
                    s[i] = s[i]-'A'+9;
                for(k = 0; k < s[i]-1; k++)
                    dp[i][s[i]] += dp[i-1][k];
                for(k = s[i]+2; k < n; k++)
                    dp[i][s[i]] += dp[i-1][k];
            }
        }
        long long ans = 0;
        for(i = 0; i < n; i++)
            ans += dp[n-1][i];
        printf("%lld\n", ans);
    }
    return 0;
}
