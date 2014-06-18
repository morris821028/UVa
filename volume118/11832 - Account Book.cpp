#include <stdio.h>
#include <string.h>
char dp[41][32767];
long long arg_1[41][32767];
long long arg_2[41][32767];
int main() {
    int n, f, A[50], i, j;
    while(scanf("%d %d", &n, &f) == 2) {
        if(n == 0)  break;
        memset(dp, 0, sizeof(dp));
        memset(arg_1, 0, sizeof(arg_1));// plus state
        memset(arg_2, 0, sizeof(arg_2));// minus state
        for(i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        dp[0][0+16000] = 1;
        for(i = 1; i <= n; i++) {
            for(j = -f; j <= f; j++) {
                if(j-A[i]+16000 >= 0 && dp[i-1][j-A[i]+16000]) {// +A[i]
                    dp[i][j+16000] = 1;
                    arg_1[i][j+16000] |= arg_1[i-1][j-A[i]+16000]|(1LL<<i);
                    arg_2[i][j+16000] |= arg_2[i-1][j-A[i]+16000];
                }
                if(j+A[i]+16000 <= f+16000 && dp[i-1][j+A[i]+16000]) {// -A[i]
                    dp[i][j+16000] = 1;
                    arg_1[i][j+16000] |= arg_1[i-1][j+A[i]+16000];
                    arg_2[i][j+16000] |= arg_2[i-1][j+A[i]+16000]|(1LL<<i);
                }
            }
        }
        if(dp[n][f+16000] == 0) {
            puts("*");
            continue;
        }
        for(i = 1; i <= n; i++) {
            if((arg_1[n][f+16000]>>i)&1) {
                if((arg_2[n][f+16000]>>i)&1)
                    putchar('?');
                else
                    putchar('+');
            } else
                putchar('-');
        }
        puts("");
    }
    return 0;
}
