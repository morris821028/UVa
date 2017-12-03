#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;

int isLeft(char c) {
    return c == '(' || c == '{' || c == '[' || c == '<';
}
int isMatch(char l, char r) {
    if (l == '(' && r == ')')
        return 1;
    if (l == '{' && r == '}')
        return 1;
    if (l == '[' && r == ']')
        return 1;
    if (l == '<' && r == '>')
        return 1;
    return 0;
}
int main() {
    int testcase, cases = 0;
    static char s[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        int n = (int) strlen(s);
        static int dp[MAXN] = {}, stk[MAXN];
        int stkIdx = -1;
        memset(dp, 0, sizeof(int)*n);
        for (int i = 0; i < n; i++) {
            if (isLeft(s[i])) {
                stk[++stkIdx] = i;
            } else {
                if (stkIdx >= 0 && isMatch(s[stk[stkIdx]], s[i])) {
                    int pos = stk[stkIdx];
                    dp[pos] = max(dp[pos], i-pos+1);
                    stkIdx--;
                } else {
                    stkIdx = -1;
                }
            }
        }
        
        // merge bracket
        for (int i = n-1; i >= 0; i--)
            dp[i] = dp[i] + dp[i + dp[i]];
        printf("Case %d:\n", ++cases);
        for (int i = 0; i < n; i++)
            printf("%d\n", dp[i]);
    }
    return 0;
}

