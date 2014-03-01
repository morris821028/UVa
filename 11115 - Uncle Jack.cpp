#include <stdio.h>

int main() {
    int x, y;
    while(scanf("%d %d", &x, &y) == 2) {
        if(!x && !y)
            break;
        int m[50][50] = {}, i, j;
        m[0][0] = 1;
        for(i = 1; i <= y; i++) {
            for(j = 0; j < 50; j++)
                m[i][j] = m[i-1][j]*x;
            for(j = 0; j < 50; j++)
                if(m[i][j] >= 10) {
                    m[i][j+1] += m[i][j]/10;
                    m[i][j] %= 10;
                }
        }
        i = 49;
        while(m[y][i] == 0) i--;
        while(i >= 0)
            putchar(m[y][i]+'0'), i--;
        puts("");
    }
    return 0;
}
