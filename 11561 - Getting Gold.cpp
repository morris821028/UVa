#include <stdio.h>
#include <string.h>
int n, m, cnt;
int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
char used[55][55] = {}, g[55][55];
void dfs(int x, int y) {
    if(g[x][y] == '#' || used[x][y])
        return;
    if(g[x][y] == 'G')
        cnt++;
    used[x][y] = 1;
    int i;
    for(i = 0; i < 4; i++)
        if(g[x+dir[i][0]][y+dir[i][1]] == 'T')
            return;
    for(i = 0; i < 4; i++)
        dfs(x+dir[i][0], y+dir[i][1]);
}
int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < m; i++)
            scanf("%s", &g[i]);
        memset(used, 0, sizeof(used));
        cnt = 0;
        j = n;
        for(i = 0; i < m && j == n; i++) {
            for(j = 0; j < n; j++)
                if(used[i][j] == 0 && g[i][j] == 'P') {
                    dfs(i, j);
                    break;
                }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
