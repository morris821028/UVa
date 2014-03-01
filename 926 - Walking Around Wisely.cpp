#include <stdio.h>

int main() {
    int t, n, m, sx, sy, ex, ey;
    int x, y, dir, i, j;
    char s[3];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
        scanf("%d", &m);
        int cant[35][35][2] = {};
        long long dp[35][35] = {};
        while(m--) {
            scanf("%d %d %s", &x, &y, s);
            if(s[0] == 'S')
                y--, dir = 1;
            else if(s[0] == 'W')
                x--, dir = 0;
            else if(s[0] == 'N')
                dir = 1;
            else    dir = 0;
            cant[x][y][dir] = 1;
        }
        dp[sx][sy] = 1;
        for(i = sx; i <= ex; i++) {
            for(j = sy; j <= ey; j++) {
                if(!cant[i][j][0])
                    dp[i+1][j] += dp[i][j];
                if(!cant[i][j][1])
                    dp[i][j+1] += dp[i][j];
            }
        }
        printf("%lld\n", dp[ex][ey]);
    }
    return 0;
}
