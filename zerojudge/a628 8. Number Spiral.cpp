#include <stdio.h>

int main() {
    int n, i, j;
    while(scanf("%d", &n) == 1) {
        int g[30][30] = {};
        int x = n/2, y = n/2+1, idx = 1, l = 2;
        while(l < n) {
            for(i = 0; i < l; i++)
                g[x--][y] = idx++;
            for(i = 0, x++, y--; i < l; i++)
                g[x][y--] = idx++;
            for(i = 0, y++, x++; i < l; i++)
                g[x++][y] = idx++;
            for(i = 0, x--, y++; i < l; i++)
                g[x][y++] = idx++;
            l += 2;
        }
        for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < n; j++)
                printf("%4d", g[i][j]);
        puts("");
    }
    return 0;
}
