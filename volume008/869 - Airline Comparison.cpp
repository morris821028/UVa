#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
    int t, n, x, y;
    char a[20], b[20];
    scanf("%d", &t);
    while(t--) {
        map<string, int> toN;
        int g1[30][30], g2[30][30];
        int size = 0, i, j, k;
        memset(g1, 1, sizeof(g1));
        memset(g2, 1, sizeof(g2));
        scanf("%d", &n);
        while(n--) {
            scanf("%s %s", a, b);
            x = toN[a];
            if(!x)
                toN[a] = ++size, x = size;
            y = toN[b];
            if(!y)
                toN[b] = ++size, y = size;
            g1[x][y] = g1[y][x] = 0;
        }
        scanf("%d", &n);
        while(n--) {
            scanf("%s %s", a, b);
            x = toN[a];
            if(!x)
                toN[a] = ++size, x = size;
            y = toN[b];
            if(!y)
                toN[b] = ++size, y = size;
            g2[x][y] = g2[y][x] = 0;
        }
        for(k = 1; k <= size; k++)
            for(i = 1; i <= size; i++)
                for(j = 1; j <= size; j++) {
                    if(g1[i][j] > g1[i][k]+g1[k][j])
                        g1[i][j] = g1[i][k]+g1[k][j];
                    if(g2[i][j] > g2[i][k]+g2[k][j])
                        g2[i][j] = g2[i][k]+g2[k][j];
                }
        for(i = 1, k = 0; i <= size; i++)
            for(j = 1; j <= size; j++)
                if(g1[i][j] != g2[i][j])
                    k = 1;
        if(k)
            puts("NO");
        else
            puts("YES");
        if(t)
            puts("");
    }
    return 0;
}
