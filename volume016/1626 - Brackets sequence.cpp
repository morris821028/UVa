#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

int dp[128][128], arg_dp[128][128];
char s[128];

void dfs(int l, int r) {
    if (l > r)  return;
    if (l == r) {
        if (s[l] == '(' || s[r] == ')')
            printf("()");
        else
            printf("[]");
        return;
    }
    int k = arg_dp[l][r];
    if (k == -1) {
        putchar(s[l]);
        dfs(l + 1, r - 1);
        putchar(s[r]);
    } else {
        dfs(l, k);
        dfs(k + 1, r);
    }
}
int main() {
    int testcase, n;
    char foo[128];
    scanf("%d", &testcase);
    while (getchar() != '\n');
    while (getchar() != '\n');
    while (testcase--) {
        gets(s);
        gets(foo);
        
        n = (int)strlen(s);
        memset(dp, 0, sizeof(dp));
        memset(arg_dp, -1, sizeof(arg_dp));
        for (int i = 0; i < n; i++) {
            for (int j = 0; i + j < n; j++) {
                if (i == 0) {
                    dp[j][j] = 1;
                    continue;
                }
                int l = j, r = i + j;
                dp[l][r] = 0x3f3f3f3f;
                if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) {
                    dp[l][r] = dp[l+1][r-1], arg_dp[l][r] = -1;
                }
                for (int k = l; k < r; k++) {
                    if (dp[l][k] + dp[k + 1][r] < dp[l][r]) {
                        dp[l][r] = dp[l][k] + dp[k + 1][r], arg_dp[l][r] = k;
                    }
                }
            }
        }
        dfs(0, n - 1);
        puts("");
        if (testcase)
            puts("");
    }
    return 0;
}
/*

*/
