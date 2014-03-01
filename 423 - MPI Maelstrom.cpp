#include <stdio.h>
#define oo 0xfffffff
int main() {
    int n, g[105][105], i, j, k, x;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            g[i][i] = oo;
        for(i = 1; i < n; i++) {
            for(j = 0; j < i; j++) {
                if(scanf("%d", &x) == 1)
                    g[i][j] = g[j][i] = x;
                else
                    g[i][j] = g[j][i] = oo, scanf("%*c");
            }
        }
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    if(g[i][j] > g[i][k]+g[k][j])
                        g[i][j] = g[i][k]+g[k][j];
        int res = 0;
        for(i = 1; i < n; i++)
            if(g[0][i] > res)
                res = g[0][i];
        printf("%d\n", res);
    }
    return 0;
}
