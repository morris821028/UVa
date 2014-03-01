#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ans = 0, astamp[10];
int H, K, use[10];
int dp[200][10] = {};
void dfs(int idx, int last, int lastcan) {
    int can = 0, i, j, k;
    for(i = lastcan; ; i++) {
        for(j = 0; j <= H; j++) {
            if(dp[i][j] != 0) {
                break;
            }
        }
        if(j == H+1) {
            can = i-1;
            break;
        }
    }
    if(idx == K) {
        if(can >= ans) {
            ans = can;
            for(i = 0; i < K; i++)
                astamp[i] = use[i];
        }
        return;
    }
    int step[10000][2], re;
    for(i = last+1; i <= can+1; i++) {
        re = 0;
        for(j = 0; j <= 100; j++) {
            for(k = 0; k < H; k++) {
                if(dp[j+i][k+1] == 0 && dp[j][k] != 0) {
                    step[re][0] = j+i;
                    step[re][1] = k+1;
                    re++;
                    dp[j+i][k+1] = 1;
                }
            }
        }
        use[idx] = i;
        dfs(idx+1, i, can);
        for(j = 0; j < re; j++)
            dp[step[j][0]][step[j][1]] = 0;
    }
}
int main() {
    while(scanf("%d %d", &H, &K) == 2) {
        if(H == 0 && K == 0)
            break;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        ans = 0;
        dfs(0, 0, 0);
        int i;
        for(i = 0; i < K; i++) {
            printf("%3d", astamp[i]);
        }
        printf(" ->%3d\n", ans);
    }
    return 0;
}
