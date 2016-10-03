#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
 
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
#define RESET(x) (mark[(x)>>5] ^= 1<<((x)&31))
#define MAXN (1000*1000)
#define MAXL (MAXN>>5)
#define AXIS(x, y) (x*1000+y)
int mark[MAXL];
int bp[1024][2];
void print(int n, int m) {
    static char g[1024];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            g[j] = GET(AXIS(i,j)) + '0';
        g[m] = '\0';
        puts(g);
    }
}
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
            SET(AXIS(sx,sy));
            bp[i][0] = sx, bp[i][1] = sy, sx += dx, sy += dy;
        }
    }
    scanf("%d", &q);
 
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    while (q--) {
        scanf("%d", &cmd);
        int cx = bp[tidx][0], cy = bp[tidx][1];
        RESET(AXIS(cx,cy));
        tidx--;
        if (tidx < 0)
            tidx = L-1;
        int tx = bp[hidx][0], ty = bp[hidx][1];
        tx += dx[cmd], ty += dy[cmd];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m || GET(AXIS(tx, ty))) {
            SET(AXIS(cx,cy));
            break;
        }
        hidx--;
        if (hidx < 0)
            hidx = L-1;
        bp[hidx][0] = tx, bp[hidx][1] = ty;
        SET(AXIS(tx,ty));
    }
    print(n, m);
    return 0;
}