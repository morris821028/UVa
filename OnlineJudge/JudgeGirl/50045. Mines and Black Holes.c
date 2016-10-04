#include <stdio.h>
 
int main() {
    int sx, sy, sz;
    int mx, my, mz;
    int bx, by, bz, has = 1;
    int n, m;
    scanf("%d %d %d", &sx, &sy, &sz);
    scanf("%d %d %d", &mx, &my, &mz);
    scanf("%d %d %d", &bx, &by, &bz);
    scanf("%d", &n);
    const int dx[] = {1, -1, 0, 0, 0, 0};
    const int dy[] = {0, 0, 1, -1, 0, 0};
    const int dz[] = {0, 0, 0, 0, 1, -1};
    for (int i = 0; i < n; i++) {
        scanf("%d", &m), m--;
        sx += dx[m], sy += dy[m], sz += dz[m];
        if (abs(sx-mx)+abs(sy-my)+abs(sz-mz) < 10)
            return 0;
        if (has && abs(sx-bx)+abs(sy-by)+abs(sz-bz) < 10) {
            sx = bx, sy = by, sz = bz;
            has = 0;
        }
        if ((i+1)%5 == 0)
            printf("%d %d %d\n", sx, sy, sz);
    }
    return 0;
}
