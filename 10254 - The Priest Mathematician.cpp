#include <stdio.h>
int bin[150][100] = {};
int dp[10000][100] = {};
void build() {
    bin[0][0] = 1;
    int i, j, k, la = 0, idx = 2;
    dp[1][0] = 1;
    for(i = 1; i < 150; i++) {
        for(j = 0; j <= la; j++)
            bin[i][j] = bin[i-1][j]*2;
        for(j = 0; j <= la; j++) {
            if(bin[i][j] >= 10) {
                bin[i][j+1] += bin[i][j]/10;
                bin[i][j] %= 10;
            }
        }
        if(bin[i][la+1]) la++;
        k = i+1;
        while(k && idx <= 10000) {
            for(j = 0; j < 99; j++)
                dp[idx][j] = dp[idx-1][j]+bin[i][j];
            for(j = 0; j < 99; j++) {
                if(dp[idx][j] >= 10) {
                    dp[idx][j+1] += dp[idx][j]/10;
                    dp[idx][j] %= 10;
                }
            }
            idx++, k--;
        }
    }
}
int main() {
    build();
    int n, i;
    while(scanf("%d", &n) == 1) {
        if(n == 0)
            putchar('0');
        for(i = 99; i >= 0; i--)
            if(dp[n][i])
                break;
        while(i >= 0)    putchar(dp[n][i]+'0'), i--;
        puts("");
    }
    return 0;
}
