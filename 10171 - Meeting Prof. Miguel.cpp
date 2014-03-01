#include <stdio.h>
#define oo 100000000

int min(int a, int b) {
    return a < b ? a : b;
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int g1[26][26], g2[26][26], i, j, k;
        int val, x, y;
        for(i = 0; i < 26; i++) {
            for(j = 0; j < 26; j++) {
                g1[i][j] = g2[i][j] = oo;
            }
            g1[i][i] = g2[i][i] = 0;
        }
        char a[10], b[10], c[10], d[10];
        for(i = 0; i < n; i++) {
            scanf("%s %s %s %s", a, b, c, d);
            scanf("%d", &val);
            x = c[0]-'A', y = d[0]-'A';
            if(a[0] == 'Y') {
                if(b[0] == 'U')
                    g1[x][y] = min(g1[x][y], val);
                else
                    g1[x][y] = g1[y][x] = min(g1[y][x], val);
            } else {
                if(b[0] == 'U')
                    g2[x][y] = min(g2[x][y], val);
                else
                    g2[x][y] = g2[y][x] = min(g2[y][x], val);
            }
        }
        scanf("%s %s", a, b);
        x = a[0]-'A', y = b[0]-'A';
        for(k = 0; k < 26; k++)
            for(i = 0; i < 26; i++)
                for(j = 0; j < 26; j++) {
                    g1[i][j] = min(g1[i][j], g1[i][k]+g1[k][j]);
                    g2[i][j] = min(g2[i][j], g2[i][k]+g2[k][j]);
                }
        int res = oo;
        for(i = 0; i < 26; i++)
            if(g1[x][i]+g2[y][i] < res)
                res = g1[x][i]+g2[y][i];
        if(res == oo)
            puts("You will never meet.");
        else {
            printf("%d", res);
            for(i = 0; i < 26; i++)
                if(g1[x][i]+g2[y][i] == res)
                    printf(" %c", i+'A');
            puts("");
        }
    }
    return 0;
}
