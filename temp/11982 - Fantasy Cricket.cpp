#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
// dp
#define MAXN 1024
#define MOD 1000000007
long long dp[MAXN][MAXN];
// dp[previous-i][reserve #U and #position]
int main() {
    int testcase, cases = 0;
    char s[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        int m = 0;
        for (int i = 0; s[i]; i++) {
            if (s[i] != 'E')
                s[m++] = s[i];
        }
        s[m] = '\0';
        
        int n = (int) strlen(s);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                dp[i][j] = 0;
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                if (s[i] == 'D') {
                    dp[i+1][j] = (dp[i+1][j] + dp[i][j] * j)%MOD;
                    // choose position to place 'D'
                    if (j) {
                        dp[i+1][j-1] = (dp[i+1][j-1] + dp[i][j] * j * j)%MOD;
                        // choose position to place 'D', and pick reserve 'U' to place this i-position
                    }
                } else if (s[i] == 'U') {
                    dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j])%MOD;
                    // reserve this 'U' and position.
                    dp[i+1][j] = (dp[i+1][j] + dp[i][j] * j)%MOD;
                    // pick reserve 'U' to place this i-position, and reserve this 'U'
                }
            }
        }
        
        long long ret = dp[n][0];
        printf("Case %d: %lld\n", ++cases, ret);
    }
    return 0;
}