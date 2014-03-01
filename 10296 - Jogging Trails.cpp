#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
int map[16][16], odd[16];
void floyd(int n) {
    int i, j, k;
    for(k = 1; k <= n; k++)
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                map[i][j] = min(map[i][j], map[i][k]+map[k][j]);
}
int dp[1<<16];
int build(int pN, int ot) {
    if(pN == 0)
        return 0;
    if(dp[pN] != -1)
        return dp[pN];
    int i, j, tmp;
    dp[pN] = 0xfffffff;
    for(i = 0; i < ot; i++) {
        if(pN&(1<<i)) {
            for(j = i+1; j < ot; j++) {
                if(pN&(1<<j)) {
                    tmp = build(pN-(1<<i)-(1<<j), ot);
                    dp[pN] = min(dp[pN], tmp+map[odd[i]][odd[j]]);
                }
            }
            break;
        }
    }
    return dp[pN];
}
int main() {
    int n, m, x, y, w;
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d", &m);
        memset(map, 63, sizeof(map));
        memset(dp, -1, sizeof(dp));
        int sum = 0, deg[16] = {};
        while(m--) {
            scanf("%d %d %d", &x, &y, &w);
            map[x][y] = min(map[x][y], w);
            map[y][x] = min(map[y][x], w);
            deg[x]++, deg[y]++;
            sum += w;
        }
        floyd(n);
        int ot = 0;
        for(int i = 1; i <= n; i++)
            if(deg[i]&1)
                odd[ot++] = i;
        printf("%d\n", sum+build((1<<ot)-1, ot));
    }
    return 0;
}
