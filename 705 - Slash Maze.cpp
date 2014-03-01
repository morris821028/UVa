#include <stdio.h>
#include <string.h>
char g[200][200][4] = {};
char used[200][200];
int n, m, cnt, maxlen;
int dfs(int x, int y, int sx, int sy, int dep) {
    if(dep > 3 && x == sx && y == sy) {
        cnt++;
        if(dep-1 > maxlen)
            maxlen = dep-1;
        return 1;
    }
    int lx = 0, rx = 2*m;
    if(x < lx || x > rx)    return 0;
    int ly = (x%2 == 0), ry = n;
    if(y < ly || y > ry)    return 0;
    if(used[x][y])  return 0;
    used[x][y] = 1;
    if(x%2 == 0) {
        int f = 0;
        if(g[x][y][0] == 0)
            f = dfs(x-1, y, sx, sy, dep+1);//0
        if(f)   return 1;
        if(g[x][y][1] == 0)
            f = dfs(x+1, y-1, sx, sy, dep+1);//1
        if(f)   return 1;
        if(g[x][y][2] == 0)
            f = dfs(x+1, y, sx, sy, dep+1);//2
        if(f)   return 1;
        if(g[x][y][3] == 0)
            f = dfs(x-1, y-1, sx, sy, dep+1);//3
        if(f)   return 1;
    } else {
        int f = 0;
        if(g[x][y][0] == 0)
            f = dfs(x-1, y+1, sx, sy, dep+1);//0
        if(f)   return 1;
        if(g[x][y][1] == 0)
            f = dfs(x+1, y, sx, sy, dep+1);//1
        if(f)   return 1;
        if(g[x][y][2] == 0)
            f = dfs(x+1, y+1, sx, sy, dep+1);//2
        if(f)   return 1;
        if(g[x][y][3] == 0)
            f = dfs(x-1, y, sx, sy, dep+1);//3
        if(f)   return 1;
    }
    return 0;
}
int main() {
    char s[200];
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)
            break;
        int i, j, k;
        memset(g, 0, sizeof(g));
        memset(used, 0, sizeof(used));
        for(i = 0; i < m; i++) {
            scanf("%s", s);
            int lx = i<<1, rx = i<<1|1;
            int ly = 1, ry = 0;
            for(j = 0; s[j]; j++) {
                if(s[j] == '\\') {
                    //g[lx][ly] -X- g[rx][ry]
                    //g[rx][ry+1] -X- g[rx+1][lx]
                    g[lx][ly][1] = 1;// can't direct
                    g[rx][ry][0] = 1;
                    g[rx][ry+1][1] = 1;
                    g[rx+1][ly][0] = 1;
                } else {
                    //g[lx][ly] -X- g[rx][ry+1]
                    //g[rx][ry] -X- g[rx+1][ly]
                    g[lx][ly][2] = 1;
                    g[rx][ry+1][3] = 1;
                    g[rx][ry][2] = 1;
                    g[rx+1][ly][3] = 1;
                }
                ly++, ry++;
            }
        }
        for(i = 0; i <= m*2; i++) {
            if(i%2 == 0)
                printf("   ");
            for(j = i%2 == 0; j <= n; j++) {
                printf("(%d%d%d%d)", g[i][j][0], g[i][j][1], g[i][j][2], g[i][j][3]);
            }
            puts("");
        }
        cnt = 0, maxlen = 0;
        for(i = 0; i <= m*2; i++) {
            for(j = (i%2 == 0); j <= n; j++)
                dfs(i, j, i, j, 1);
        }
        /*for(int i = 0; i <= m*2; i++) {
            if(i%2 == 0)
                printf(" ");
            for(int j = i%2 == 0; j <= n; j++) {
                printf("(%d)", used[i][j]);
            }
            puts("");
        }*/
        printf("Maze #%d:\n", ++cases);
        if(cnt)
            printf("%d Cycles; the longest has length %d.\n", cnt, maxlen);
        else
            puts("There are no cycles.");
        puts("");
    }
    return 0;
}
/*
6 4
\//\\/
\///\/
//\\/\
\/\///
3 3
///
\//
\\\
2 2
/\
\/
0 0
*/
