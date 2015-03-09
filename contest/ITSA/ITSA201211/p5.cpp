#include <stdio.h>
#include <string.h>
char x[105], y[105];
int dp[105][105], arg[105][105];
void print(int i, int j) {
    if(dp[i][j] == 0)   return;
    if(arg[i][j] == 1) {
        print(i-1, j-1);
        printf("%c", x[i-1]);
    } else if(arg[i][j] == 2) {
        print(i-1, j);
    } else
        print(i, j-1);
}
int main() {
    int i, j;
    while(scanf("%s %s", x, y) == 2) {
        int la = strlen(x), lb = strlen(y);
        memset(dp, 0, sizeof(dp));
        for(i = 1; i <= la; i++) {
            for(j = 1; j <= lb; j++) {
                if(x[i-1] == y[j-1]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                    arg[i][j] = 1;
                } else {
                    if(dp[i-1][j] > dp[i][j-1]) {
                        dp[i][j] = dp[i-1][j];
                        arg[i][j] = 2;
                    } else {
                        dp[i][j] = dp[i][j-1];
                        arg[i][j] = 3;
                    }
                }
            }
        }
        if(dp[la][lb] == 0)
            puts("none");
        else
            print(la, lb), puts("");
    }
    return 0;
}
/*
*/
