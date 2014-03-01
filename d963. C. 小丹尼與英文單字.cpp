#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
short dp[5005][5005];
int main() {
    int t, i, j;
    char s[5005];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int len = strlen(s);
        for(i = 0; i < len; i++) {
            for(j = 0; i+j < len; j++) {
                if(i == 0)
                    dp[j][j] = 1;
                else if(s[j] == s[i+j])
                    dp[j][j+i] = dp[j+1][j+i-1]+2;
                else
                    dp[j][j+i] = max(dp[j][j+i-1], dp[j+1][j+i]);
            }
        }
        printf("%d\n", dp[0][len-1]);
    }
    return 0;
}
