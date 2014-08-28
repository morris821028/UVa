#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char g[128][128];
int freedom, enemy, fighting, sector, n;

int check(int x, int y, int c) {
    int ret = 0, tx, ty;
    g[x][y] = '*';
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        if (tx < 0 || ty < 0 || tx >= n || ty >= n)
            continue;
        if ((g[tx][ty] == 'P' && c == 'B') || (g[tx][ty] == 'B' && c == 'P')) {
            ret = 1;
        }
        if (g[tx][ty] == c)
            ret |= check(tx, ty, c);
    }
    return ret;
}
void dfs(int x, int y) {
    if (g[x][y] == 'B') {
        freedom++;
        if (check(x, y, 'B')) {
            fighting += 2;
        }
    }
    if (g[x][y] == 'P') {
        enemy++;
        if (check(x, y, 'P')) {
            fighting += 2;
        }
    }
    g[x][y] = '.';
    int tx, ty;
    for (int i = 0; i < 4; i++) {
        tx = x + dx[i], ty = y + dy[i];
        if (tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == '.')
            continue;
        dfs(tx, ty);
    }
}
int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
            scanf("%s", g[i]);
        }
        fighting = 0, sector = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] != '.') {
                    freedom = enemy = 0;
                    dfs(i, j);
                    printf("Sector #%d: contain %d freedom fighter group(s) & %d enemy group(s)\n", ++sector, freedom, enemy);
                }
            }
        }
        printf("Total %d group(s) are in fighting position.\n\n", fighting);
    }
    return 0;
}
/*
 16
 ................
 ................
 .******.........
 .**PP**....***..
 .******....*B*..
 .******....***..
 .**BB**.........
 .******.........
 ................
 .....*******....
 ....*BB**BB**...
 ....*BB**PP**...
 ....*********...
 ....****PP***...
 .....*******....
 ................

 0
 
 */