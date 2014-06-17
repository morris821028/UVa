#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
short dp[1005][1005];
char used[1005][1005];
int main() {
    char s[1005], rs[1005];
    int n, i, j;
    while(gets(s)) {
        n = strlen(s);
        for(i = 0; i < n; i++)
            rs[i] = s[n-i-1];
        rs[n] = '\0';
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                if(s[i-1] == rs[j-1])
                    dp[i][j] = dp[i-1][j-1]+1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                used[i][j] = 0;
            }
        }
        int len = dp[n][n], x, y;
        queue<int> X, Y, rX, rY;
        char ans[1005];
        for(i = len/2; i >= 0; i--) {
            char output = 127;
            if(i == len/2) {
                X.push(n), Y.push(n);
                used[n][n] = 1;
                if(s[n-1] == rs[n-1])
                    output = s[n-1];
            }
            while(!X.empty()) { // equal
                x = X.front(), X.pop();
                y = Y.front(), Y.pop();
                rX.push(x), rY.push(y);
                if(s[x-1] == rs[y-1])
                    output = min(output, s[x-1]);
                if(dp[x-1][y] == dp[x][y] && used[x-1][y] == 0)
                    used[x-1][y] = 1, X.push(x-1), Y.push(y);
                if(dp[x][y-1] == dp[x][y] && used[x][y-1] == 0)
                    used[x][y-1] = 1, X.push(x), Y.push(y-1);
            }
            ans[i] = output;
            putchar(output);
            while(!rX.empty()) {
                x = rX.front(), rX.pop();
                y = rY.front(), rY.pop();
                if(s[x-1] == rs[y-1] && s[x-1] == output) {
                    X.push(x-1), Y.push(y-1);
                    used[x-1][y-1] = 1;
                }
            }
        }
        for(i = 1+(len%2 == 0); i <= len/2; i++)
            putchar(ans[i]);
        puts("");
    }
    return 0;
}
/*
aabbaabb
computer
abzla
samhita
*/
