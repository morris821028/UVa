#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    char cmd[300];
    int dp[300], way[300];
    gets(cmd);
    while(gets(cmd)) {
        int cnt[26] = {}, i, j;
        for(i = 0; cmd[i]; i++) {
            if(cmd[i] >= 'A' && cmd[i] <= 'Z')
                cnt[cmd[i]-'A']++;
        }
        for(i = 0, j = 0; i < 26; i++)
            if(cnt[i])
            cmd[j++] = i+1;
        int n = j;
        int mx = 0, mxway;
        for(i = 0; i < n; i++) {
            dp[i] = 1, way[i] = 0;
            for(j = 0; j < i; j++)
                if(cmd[j]*5 <= cmd[i]*4)
                    dp[i] = max(dp[i], dp[j]+1);
            for(j = 0; j < i; j++)
                if(cmd[j]*5 <= cmd[i]*4 && dp[i] == dp[j]+1)
                    way[i] += way[j];
            if(dp[i] == 1)  way[i] = 1;
            if(dp[i] > mx)  mx = dp[i], mxway = 0;
            if(dp[i] == mx) mxway += way[i];
        }
        printf("%d %d\n", mx, mxway);
    }
    return 0;
}
