#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
// dp
#define MAXN 1024
#define MOD 1000000007
int dp[MAXN][MAXN], sum[MAXN][MAXN];
// dp[previous i-th][tail number of sequence] = way
// {3, 1, 2, 7, 4, 6, 5} => add 3 to tail => {4, 1, 2, 8, 5, 7, 6, 3}
// if we add x to tail, make seq[i]++ which seq[i] >= x
int main() {
    char s[MAXN];
    while (scanf("%s", s) == 1) {
        int n = (int) strlen(s);
        for (int i = 0; i <= n+1; i++)
            for (int j = 0; j <= n+1; j++)
                dp[i][j] = 0, sum[i][j] = 0;
        dp[0][1] = sum[0][1] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= i+2; j++) {
                if (s[i] == 'I' || s[i] == '?')
                    dp[i+1][j] = (dp[i+1][j] + sum[i][j-1])%MOD;
                if (s[i] == 'D' || s[i] == '?')
                    dp[i+1][j] = (dp[i+1][j] + (sum[i][i+1] - sum[i][j-1])%MOD + MOD)%MOD;
                sum[i+1][j] = (sum[i+1][j-1] + dp[i+1][j])%MOD;
//                printf("%d %d %d\n", i+1, j, dp[i+1][j]);
            }
        }
        printf("%d\n", sum[n][n+1]);
    }
    return 0;
}