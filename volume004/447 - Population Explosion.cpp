#include <stdio.h>
#include <string.h>

int cntP(int x, int y, int g[][21]) {
    int i, j, cnt = 0;
    int tx, ty;
    for(i = -1; i <= 1; i++) {
        for(j = -1; j <= 1; j++) {
            tx = x+i, ty = y+j;
            if(tx < 0 || ty < 0 || tx >= 20 || ty >= 20)
                continue;
            if(i == 0 && j == 0)
                continue;
            cnt += g[tx][ty];
        }
    }
    return cnt;
}
int main() {
    int t;
    scanf("%d", &t);
    while(getchar() != '\n');
    while(getchar() != '\n');
    char asterisk[] = "********************";
    char s[50];
    while(t--) {
        gets(s);
        int Y, g[2][21][21] = {};
        int x, y, i, j, k, roll = 0, pre;
        sscanf(s, "%d", &Y);
        while(gets(s) && s[0]) {
            sscanf(s, "%d %d", &x, &y);
            g[roll][--x][--y] = 1;
        }
        puts(asterisk);
        for(i = 0; i < Y; i++) {
            for(j = 0; j < 20; j++, puts("")) {
                for(k = 0; k < 20; k++) {
                    if(g[roll][j][k]) {
                        putchar('O');
                    } else
                        putchar(' ');
                }
            }
            memset(g[1-roll], 0, sizeof(g[roll]));
            for(j = 0; j < 20; j++) {
                for(k = 0; k < 20; k++) {
                    int f = cntP(j, k, g[roll]);
                    if(g[roll][j][k]) {
                        if(f == 2 || f == 3)
                            g[1-roll][j][k] = 1;
                    } else {
                        if(f == 3)
                            g[1-roll][j][k] = 1;
                    }
                }
            }
            puts(asterisk);
            roll = 1-roll;
        }
        if(t)
            puts("");
    }
    return 0;
}
