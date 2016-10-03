#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
 
char g[1024][1024];
int bp[1024][2];
int main() {
    int n, m;
    int sx, sy, ex, ey;
    int q, cmd;
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
    int L = abs(sx-ex)+abs(sy-ey)+1;
    int hidx = 0, tidx = L-1;
    {
        int dx = sx < ex ? 1 : (sx > ex ? -1 : 0);
        int dy = sy < ey ? 1 : (sy > ey ? -1 : 0);
        for (int i = 0; i < L; i++) {
            g[sx][sy] = 1;
            bp[i][0] = sx, bp[i][1] = sy, sx += dx, sy += dy;
        }
    }
    scanf("%d", &q);
 
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    while (getchar() != '\n');
    while (q--) {
        cmd = getchar() - '0', getchar();
        int cx = bp[tidx][0], cy = bp[tidx][1];
        g[cx][cy] = 0;
        tidx--;
        if (tidx < 0)
            tidx = L-1;
        int tx = bp[hidx][0], ty = bp[hidx][1];
        tx += dx[cmd], ty += dy[cmd];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m || g[tx][ty]) {
            g[cx][cy] = 1;
            break;
        }
        hidx--;
        if (hidx < 0)
            hidx = L-1;
        bp[hidx][0] = tx, bp[hidx][1] = ty;
        g[tx][ty] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            g[i][j] += '0';
        g[i][m] = '\0';
        puts(g[i]);
    }
    return 0;
}