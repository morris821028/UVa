#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int dp[1005][1005];
int main() {
    int t, cases = 0, i, j;
    char s[1005];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        for(i = 0; i < len; i++) {
            for(j = 0; j+i < len; j++) {
                if(s[j] == s[i+j]) {
                    dp[j][i+j] = i < 2 ? 0 : dp[j+1][i+j-1];
                } else {
                    dp[j][i+j] = min(dp[j+1][i+j], dp[j][i+j-1]);
                    if(j+1 <= i+j-1)
                        dp[j][i+j] = min(dp[j][i+j], dp[j+1][i+j-1]);
                    dp[j][i+j]++;
                }
            }
        }
        printf("Case %d: %d\n", ++cases, dp[0][len-1]);
    }
    return 0;
}
