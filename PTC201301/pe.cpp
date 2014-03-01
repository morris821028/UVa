#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int g[105][105] = {}, used[105][105];
void dfs(int x, int y) {
    if(x < 0 || y < 0 || x > 100 || y > 100)
        return;
    if(used[x][y] || g[x][y] == 1)  return;
    used[x][y] = 1;
    dfs(x+1, y);
    dfs(x, y+1);
    dfs(x-1, y);
    dfs(x, y-1);
    if(x+1 < 100 && g[x+1][y] == 1)
        g[x][y] = 2;
    if(x-1 >= 0 && g[x-1][y] == 1)
        g[x][y] = 2;
    if(y+1 < 100 && g[x][y+1] == 1)
        g[x][y] = 2;
    if(y-1 < 100 && g[x][y-1] == 1)
        g[x][y] = 2;

    if(x+1 < 100 && y+1 < 100 && g[x+1][y+1] == 1)
        g[x][y] = 2;
    if(x+1 < 100 && y-1 >= 0 && g[x+1][y-1] == 1)
        g[x][y] = 2;
    if(x-1 >= 0 && y+1 < 100 && g[x-1][y+1] == 1)
        g[x][y] = 2;
    if(x-1 >= 0 && y-1 >= 0 && g[x-1][y-1] == 1)
        g[x][y] = 2;
}
int main() {
    int m, n, p, q;
    int x[1024], y[1024];
    int i, j, k;
    while(scanf("%d %d", &m, &n) == 2) {
        scanf("%d %d", &p, &q);
        for(i = 0; i < q; i++)
            scanf("%d %d", &x[i], &y[i]);
        x[q] = x[0], y[q] = y[0];
        memset(g, 0, sizeof(g));
        memset(used, 0, sizeof(used));
        for(i = 0; i < q; i++) {
            int lx, ly, rx, ry;
            lx = min(x[i], x[i+1]);
            ly = min(y[i], y[i+1]);
            rx = max(x[i], x[i+1]);
            ry = max(y[i], y[i+1]);
            for(j = lx-p+1; j < rx+p; j++)
                for(k = ly-p+1; k < ly+p; k++)
                    g[j][k] = 1;
        }
        dfs(0, 0);
  /*      for(i = 0; i < 20; i++, puts(""))
            for(j = 0; j < 20; j++)
                printf("%d", g[i][j]);
*/
        for(j = 0; j < 100; j++)
        for(i = 0; i < 100; i++)
                if(g[i][j])
                    printf("%d %d\n", i, j);
    }
    return 0;
}
/*
9 12
1
8
3 3
6 3
6 4
5 4
5 5
4 5
4 4
3 4
*/
