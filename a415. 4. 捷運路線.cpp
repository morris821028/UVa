#include <stdio.h>

int main() {
    int n, m;
    int i, j;
    while(scanf("%d %d", &n, &m) == 2) {
        int x, t;
        int g[101][21], gt[101];
        int ch[101][21][101][2];
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &t);
            gt[x] = t;
            for(j = 1; j <= t; j++)
                scanf("%d", &g[x][j]);
        }

    }
    return 0;
}
