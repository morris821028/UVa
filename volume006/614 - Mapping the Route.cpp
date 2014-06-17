#include <stdio.h>
#include <string.h>
int g[20][20], dg[20][20];
int sx, sy, ex, ey, n, m;
int check(int x, int y, int v) {
    if(x <= 0 || x > n || y <= 0 || y > m)
        return 0;
    if(dg[x][y]&v)
        return 0;
    return 1;
}
int dfs(int x, int y, int dep) {
    if(x == ex && y == ey) {
        g[x][y] = dep;
        return 1;
    }
    if(x <= 0 || x > n || y <= 0 || y > m)
        return 0;
    if(g[x][y])
        return 0;
    g[x][y] = dep;
    int f = 0;
    if(check(x, y-1, 1))
        f = dfs(x, y-1, dep+1); // W
    if(f)   return 1;
    if(check(x-1, y, 2))
        f = dfs(x-1, y, dep+1); // N
    if(f)   return 1;
    if(check(x, y, 1))
        f = dfs(x, y+1, dep+1); // E
    if(f)   return 1;
    if(check(x, y, 2))
        f = dfs(x+1, y, dep+1); // S
    if(f)   return 1;
    g[x][y] = -1;
    if(x == sx && y == sy)
        g[x][y] = 1;
    return 0;
}
int main() {
    int cases = 0;
    int i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
        memset(g, 0, sizeof(g));
        for(i = 1; i <= n; i++)
            for(j = 1; j <= m; j++)
                scanf("%d", &dg[i][j]);
        dfs(sx, sy, 1);
        printf("Maze %d\n\n", ++cases);
        for(i = 1, putchar('+'); i <= m; i++)
            printf("---+");
        puts("");
        for(i = 1; i <= n; i++) {
            putchar('|');
            for(j = 1; j <= m; j++) {
                if(g[i][j] < 0)
                    printf("???");
                else if(g[i][j] == 0)
                    printf("   ");
                else
                    printf("%3d", g[i][j]);
                if(j == m || (dg[i][j]&1))
                    putchar('|');
                else
                    putchar(' ');
            }
            puts("");
            for(j = 1, putchar('+'); j <= m; j++) {
                if(i == n || (dg[i][j]&2))
                    printf("---+");
                else
                    printf("   +");
            }
            puts("");
        }
        puts("\n");
    }
    return 0;
}
