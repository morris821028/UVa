#include <stdio.h>
#include <string.h>
int main() {
    int t;
    char s[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int i, j, len = strlen(s);
        long long dp[65][65] = {};
        for(i = 0; i < len; i++) {
            for(j = 0; j+i < len; j++) {
                if(i == 0)
                    dp[j][j] = 1;
                else if(s[j] == s[j+i])
                    dp[j][j+i] = dp[j][j+i-1]+dp[j+1][j+i]+1;
                else
                    dp[j][j+i] = dp[j][j+i-1]+dp[j+1][j+i]-dp[j+1][j+i-1];
            }
        }
        printf("%lld\n", dp[0][len-1]);
    }
    return 0;
}
