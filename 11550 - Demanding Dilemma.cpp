#include <stdio.h>

int main() {
    int vg[10][100];
    int n, m, i, j;
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                scanf("%d", &vg[i][j]);
        int g[10][10] = {}, err = 0, x, y;
        for(i = 0; i < m && !err; i++) {
            int cnt = 0;
            for(j = 0; j < n; j++) {
                if(vg[j][i]) {
                    if(cnt == 0)    x = j;
                    else            y = j;
                    cnt++;
                }
            }
            if(cnt != 2)    err = 1;
            else {
                if(g[x][y]) err = 1;
                g[x][y] = g[y][x] = 1;
            }
        }
        puts(err ? "No" : "Yes");
    }
    return 0;
}
