#include <stdio.h>
#include <string.h>
int dp[4][4][1<<16];
int dx[8] = {0,0,1,1,1,-1,-1,-1};
int dy[8] = {1,-1,0,1,-1,0,1,-1};
int dfs(int mask, int r, int c) {
    if(dp[r][c][mask] != -1)
        return dp[r][c][mask];
    int i, j, k, o1, o2, o3, tx, ty, x, y, mask2;
    int &res = dp[r][c][mask];
    res = 0;
    for(i = 0; i <= r; i++) {
        for(j = 0; j <= c; j++) {
            o3 = i*4+j;
            if((mask>>o3)&1) {
                for(k = 0; k < 8; k++) {
                    tx = i+dx[k], ty = j+dy[k];
                    x = i+2*dx[k], y = j+2*dy[k];
                    if(tx < 0 || tx > r || ty < 0 || ty > c)
                        continue;
                    if(x < 0 || x > r || y < 0 || y > c)
                        continue;
                    o1 = tx*4+ty, o2 = x*4+y;
                    if(!((mask>>o1)&1) || ((mask>>o2)&1))
                        continue;
                    mask2 = mask ^ (1<<o1) ^ (1<<o2) ^ (1<<o3);
                    res += dfs(mask2, r, c);
                }
            }
        }
    }
    return res;
}
int main() {
    memset(dp, -1, sizeof(dp));
    int i, j, k;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            for(k = 0; k < 16; k++)
                dp[i][j][1<<k] = 1;
        }
    }
    int testcase, R, C, N, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &R, &C, &N);
        int x, y, mask = 0;
        while(N--) {
            scanf("%d %d", &x, &y);
            x--, y--;
            mask |= 1<<(x*4+y);
        }
        R--, C--;
        printf("Case %d: %d\n", ++cases, dfs(mask, R, C));
    }
    return 0;
}
/*
3
3 3 3
3 1
2 2
1 2
*/
