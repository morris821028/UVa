#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int testcase, cases = 0;
    char s[1024];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%s", s);
        int n = strlen(s);
        int dp[1024][24], inf;
        int i, j, k;
        memset(dp, 63, sizeof(dp));
        inf = dp[0][0];
        dp[0][6] = 0;
        for(i = 0; i < n; i++) {//where
            for(j = 0; j < 24; j++) {//time
                if(dp[i][j] == inf)
                    continue;
                int night = 0, jungle = 0;
                for(k = 1; k <= 16; k++) {//walk time
                    int time = (j+k)%24;
                    if(time >= 18 || time <= 6)
                            night = 1;
                    else    night = 0, jungle = 0;
                    if(s[i+k] == '*' && night)
                        jungle = 1;
                    if(night && jungle)
                        break;
                    if(s[i+k] != '*') {
                        dp[i+k][(time+8)%24] = min(dp[i+k][(time+8)%24], dp[i][j]+k+8);
                        dp[i+k][(time+16)%24] = min(dp[i+k][(time+16)%24], dp[i][j]+k+16);
                    }
                }
            }
        }
        int ret = inf;
        /*for(j = 0; j < 1; j++, puts("")) {
            printf("%2d:", j);
            for(i = 0; i < n; i++) {
                printf("%2c", s[i]);
            }
        }
        for(j = 0; j < 24; j++, puts("")) {
            printf("%2d:", j);
            for(i = 0; i < n; i++) {
                if(dp[i][j] == inf) printf("##");
                else    printf("%2d", dp[i][j]);
            }
        }*/
        for(i = 0; i < 24; i++)
            ret = min(ret, dp[n-1][i]);
        printf("Case #%d: ", ++cases);
        if(ret == inf)
            puts("-1");
        else
            printf("%d\n", ret-8);
    }
    return 0;
}
