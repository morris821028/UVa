#include <stdio.h>
#include <string.h>
char g[105][105];
int used[105][105], n;
void dfs(int x, int y, int w) {
    if(x < 0 || y < 0 || x >= n || y >= n)
        return ;
    if(used[x][y] || g[x][y] != w)
        return ;
    used[x][y] = 1;
    dfs(x+1, y, w);
    dfs(x-1, y, w);
    dfs(x, y+1, w);
    dfs(x, y-1, w);
}
int main() {
    int i, j, p, q;
    while(scanf("%d", &n) == 1 && n) {
        memset(used, 0, sizeof(used));
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        for(i = 0; i < n; i++) {
            if(g[i][0] == 'W')
                dfs(i, 0, 'W');
            if(g[0][i] == 'B')
                dfs(0, i, 'B');
        }
        int Wwin = 0, Bwin = 0;
        for(i = 0; i < n; i++) {
            if(used[i][n-1] && g[i][n-1] == 'W')
                Wwin = 1;
            if(used[n-1][i] && g[n-1][i] == 'B')
                Bwin = 1;
        }
        if(Wwin) {
            puts("White has a winning path.");
            continue;
        }
        if(Bwin) {
            puts("Black has a winning path.");
            continue;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(g[i][j] == 'U' && !Wwin) {
                    memset(used, 0, sizeof(used));
                    g[i][j] = 'W';
                    for(p = 0; p < n; p++)
                        if(g[p][0] == 'W')
                            dfs(p, 0, 'W');
                    for(p = 0; p < n; p++)
                        if(used[p][n-1] && g[p][n-1] == 'W')
                            Wwin = 1;
                    g[i][j] = 'U';
                }
            }
        }
        if(Wwin) {
            puts("White can win in one move.");
            continue;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(g[i][j] == 'U' && !Bwin) {
                    memset(used, 0, sizeof(used));
                    g[i][j] = 'B';
                    for(p = 0; p < n; p++)
                        if(g[0][p] == 'B')
                            dfs(0, p, 'B');
                    for(p = 0; p < n; p++)
                        if(used[n-1][p] && g[n-1][p] == 'B')
                            Bwin = 1;
                    g[i][j] = 'U';
                }
            }
        }
        if(Bwin) {
            puts("Black can win in one move.");
            continue;
        }
        puts("There is no winning path.");
    }
    return 0;
}
