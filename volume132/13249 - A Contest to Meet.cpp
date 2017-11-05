#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

static const int MAXN = 128;
int main() {
    int n, m;
    static int f[MAXN][MAXN];
    while (scanf("%d %d", &n, &m) == 2) {
        memset(f, 0x3f, sizeof(f));
        for (int i = 0; i < n; i++)
            f[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            f[x][y] = f[y][x] = min(f[x][y], w);
        }
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    f[j][k] = min(f[j][k], f[j][i]+f[i][k]);
        int ret = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ret = max(ret, f[i][j]);
        
        int sA, sB, sC;
        scanf("%d %d %d", &sA, &sB, &sC);
        sA = min(sA, min(sB, sC));
        printf("%d\n", (ret+sA-1)/sA);
    }
    return 0;
}
/*
 2 1
 0 1 150
 60 50 75
 3 2
 1 0 100
 1 2 80
 60 80 50
 4 5
 0 1 200
 0 2 200
 0 3 200
 2 1 200
 2 3 200
 50 100 100
*/

