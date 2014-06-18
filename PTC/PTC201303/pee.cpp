#include <stdio.h>
#include <string.h>
int used[105][150] = {};
int dirx[8] = {-2,-1,1,2,2,1,-1,-2};
int diry[8] = {1,2,2,1,-1,-2,-2,-1};
int n, flag = 0;
int check(int x, int y) {
    int tx, ty, i, cnt = 0;
    for(i = 0; i < 8; i++) {
        tx = x+dirx[i];
        ty = y+diry[i];
        if(tx <= 0 || ty <= 0 || tx > n || ty > n)
            continue;
        if(used[tx][ty])
            continue;
        cnt++;
    }
    return cnt;
}
void dfs(int x, int y, int dep) {
    if(flag)    return;
    if(dep == n*n) {
        int i, j;
        for(i = 1; i <= n; i++, puts(""))
            for(j = 1; j <= n; j++)
                printf("%5d", used[i][j]);
        flag = 1;
        return ;
    }
    int tx, ty, i, d[8], j;
    for(i = 0; i < 8; i++) {
        tx = x+dirx[i];
        ty = y+diry[i];
        if(tx <= 0 || ty <= 0 || tx > n || ty > n)
            continue;
        if(used[tx][ty])
            continue;
        d[i] = check(tx, ty);
        /*used[tx][ty] = dep+1;
        dfs(tx, ty, dep+1);
        used[tx][ty] = 0;*/
    }
    for(j = 0; j < 8; j++)
    for(i = 0; i < 8; i++) {
        tx = x+dirx[i];
        ty = y+diry[i];
        if(tx <= 0 || ty <= 0 || tx > n || ty > n)
            continue;
        if(used[tx][ty])
            continue;
        if(d[i] != j)
            continue;
        used[tx][ty] = dep+1;
        dfs(tx, ty, dep+1);
        used[tx][ty] = 0;
    }
}
int main() {
    int t, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        scanf("%d %d", &x, &y);
        flag = 0;
        memset(used, 0, sizeof(used));
        used[x][y] = 1;
        dfs(x, y, 1);
        used[x][y] = 0;
        puts("");
    }
    return 0;
}
