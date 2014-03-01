#include <stdio.h>
int n, m;
int used[105][105] = {}, g[105][105];
int rx, ry, flag;
void dfs(int x, int y, int p, int q) {
    if(x >= n || x < 0 || y >= m || y < 0)
        return;
    if(x == n-1) {
        if(y < ry)
            ry = y;
        flag = 1;
        return;
    }
    if(used[x][y])  return;
    if(g[x][y] != p)    return;
    if(p == q) {
        p = 0;
        q++;
    }
    used[x][y] = 1;
    dfs(x, y+1, p+1, q);
    dfs(x, y-1, p+1, q);
    dfs(x+1, y, p+1, q);
    dfs(x-1, y, p+1, q);
    used[x][y] = 0;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                scanf("%d", &g[i][j]);
        for(i = 0; i < m; i++) {
            flag = 0;
            rx = n-1, ry = 0xffff;
            dfs(0, i, 1, 1);
            if(flag)
                break;
        }
        printf("%d %d\n%d %d\n", 1, i+1, rx+1, ry+1);
        if(t)
            puts("");
    }
    return 0;
}
