#include <stdio.h>
char pa[500][500][60] = {};
int main() {
    int t, i, j, k;
    pa[0][0][0] = 1;
    for(i = 1; i < 500; i++) {
        pa[i][0][0] = 1;
        for(j = 1; j <= i; j++) {
            for(k = 0; k < 60; k++)
                pa[i][j][k] += pa[i-1][j-1][k]+pa[i-1][j][k];
            for(k = 0; k < 59; k++)
                if(pa[i][j][k] >= 10) {
                    pa[i][j][k+1] += pa[i][j][k]/10;
                    pa[i][j][k] %= 10;
                }
        }
    }

    scanf("%d", &t);
    while(t--) {
        int n, m, x, y, i;
        scanf("%d %d", &n, &m);
        x = n;
        for(i = 0; i < m; i++) {
            scanf("%d", &y);
            x -= y;
        }
        x -= m-1;
        if(x+m < m || m < 0) {
            puts("0");
            continue;
        }
        k = 59;
        while(k >= 0 && pa[x+m][m][k] == 0)   k--;
        if(k < 0) {
            puts("0");
            continue;
        }
        while(k >= 0)
            putchar(pa[x+m][m][k]+'0'), k--;
        puts("");

    }
    return 0;
}
/*
3
25 5 2 3 2 8 1
*/
