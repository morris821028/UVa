#include <stdio.h>
#define oo 100000000
int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int n, m, cases = 0, i, j, k;
    int g[105][105], x, y, v;
    scanf("%*d");
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++)
                g[i][j] = oo;
            g[i][i] = 0;
        }
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            g[x][y] = g[y][x] = min(g[y][x], v);
        }
        for(k = 1; k <= n; k++)
            for(i = 1; i <= n; i++)
                for(j = 1; j <= n; j++)
                    g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
        int res = oo;
        for(i = 6; i <= n; i++) {
            for(j = 1; j <= 5; j++)
                if(g[i][j] != g[i][1])
                    break;
            if(j == 6) {
                int tmp = 0;
                for(j = 1; j <= n; j++)
                    tmp = max(tmp, g[i][j]);
                res = min(tmp, res);
            }
        }
        printf("Map %d: ", ++cases);
        if(res == oo)   puts("-1");
        else            printf("%d\n", res);
    }
    return 0;
}
