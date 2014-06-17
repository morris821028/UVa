#include <stdio.h>
#define oo 0xffffff
#define min(x, y) ((x)<(y)?(x):(y))
#define max(x, y) ((x)>(y)?(x):(y))
int main() {
    int n, m, q, cases = 0;
    while(scanf("%d %d %d", &n, &m, &q) == 3) {
        if(n == 0)  break;
        int f[101][101], i, j, k, x, y, b;
        for(i = 1; i <= n; f[i][i] = 0, i++)
            for(j = 1; j <= n; j++)
                f[i][j] = oo;
        while(m--) {
            scanf("%d %d %d", &x, &y, &b);
            f[x][y] = min(f[x][y], b);
            f[y][x] = f[x][y];
        }
        for(k = 1; k <= n; k++)
            for(i = 1; i <= n; i++)
                for(j = 1; j <= n; j++)
                    f[i][j] = min(f[i][j], max(f[i][k], f[k][j]));
        if(cases)
            puts("");
        printf("Case #%d\n", ++cases);
        while(q--) {
            scanf("%d %d", &x, &y);
            if(f[x][y] != oo)
                printf("%d\n", f[x][y]);
            else
                puts("no path");
        }
    }
    return 0;
}
