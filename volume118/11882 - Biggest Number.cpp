#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <stdlib.h>
using namespace std;
char g[35][35];
char ans[35], used[20][20], tmp[35];
int alen = 1;
int n, m;
int check(int x, int y, int dep) {
    if(x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    if(g[x][y] < '0' || g[x][y] > '9')
        return 0;
    if(used[x][y])
        return 0;
    char u2[16][16] = {};
    static int X[30], Y[30];
    static int i, j, tx, ty, Qt;
    static int dirx[4] = {0,0,1,-1};
    static int diry[4] = {1,-1,0,0};
    Qt = 0, X[Qt] = x, Y[Qt] = y;
    u2[x][y] = 1;
    for(i = 0; i <= Qt; i++) {
        x = X[i], y = Y[i];
        tmp[dep+i] = g[x][y];
        for(j = 0; j < 4; j++) {
            tx = x+dirx[j];
            ty = y+diry[j];
            if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                continue;
            if(used[tx][ty] || u2[tx][ty])
                continue;
            if(g[tx][ty] < '0' || g[tx][ty] > '9')
                continue;
            Qt++;
            X[Qt] = tx, Y[Qt] = ty;
            u2[tx][ty] = 1;
        }
        if(dep+Qt+1 > alen) return 1;
    }
    if(dep+Qt+1 < alen) return 0;
    sort(tmp+dep+1, tmp+dep+Qt+1, greater<char>());
    tmp[dep+Qt+1] = '\0';
    for(i = 0; i < alen; i++)
        if(tmp[i] > ans[i])
            return 1;
        else if(tmp[i] < ans[i])
            return 0;
    return 1;
}
void dfs(int x, int y, int dep) {
    int test = 0;
    if(check(x-1, y, dep)) {
        tmp[dep] = g[x-1][y];
        used[x-1][y] = 1;
        dfs(x-1, y, dep+1);
        used[x-1][y] = 0;
        test = 1;
    }
    if(check(x, y-1, dep)) {
        tmp[dep] = g[x][y-1];
        used[x][y-1] = 1;
        dfs(x, y-1, dep+1);
        used[x][y-1] = 0;
        test = 1;
    }
    if(check(x+1, y, dep)) {
        tmp[dep] = g[x+1][y];
        used[x+1][y] = 1;
        dfs(x+1, y, dep+1);
        used[x+1][y] = 0;
        test = 1;
    }

    if(check(x, y+1, dep)) {
        tmp[dep] = g[x][y+1];
        used[x][y+1] = 1;
        dfs(x, y+1, dep+1);
        used[x][y+1] = 0;
        test = 1;
    }
    if(!test) {
        if(dep < alen)  return ;
        int i;
        if(dep == alen) {
            for(i = 0; i < dep; i++)
                if(tmp[i] < ans[i])
                    return;
                else if(tmp[i] > ans[i])
                    break;
        }
        tmp[dep] = '\0';
        for(i = 0; i < dep; i++)
            ans[i] = tmp[i];
        ans[dep] = '\0';
        alen = dep;
    }
}
int main() {
    int i, j, k;
    srand(1028);
    while(scanf("%d %d", &n, &m) == 2 && n) {
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        ans[0] = '0', ans[1] = '\0';
        alen = 1;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] >= '1' && g[i][j] <= '9') {
                    used[i][j] = 1;
                    tmp[0] = g[i][j];
                    dfs(i, j, 1);
                    used[i][j] = 0;
                }
            }
        }
        printf("%s\n", ans);
    }
    return 0;
}
/*
6 5
11111
11111
11111
11111
11111
11111
6 5
12345
65498
65416
65498
65487
98754

987868549145543216666985544754

3 7
##9784#
##123##
##45###
*/
