#include <stdio.h>

int main() {
    int cases = 0, t;
    char cmd[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", cmd);
        printf("Case #%d:\n", ++cases);
        char g[205][205] = {};
        int y = 100, mx = 100, mn = 100;
        int i, j, k, len;
        for(i = 0; cmd[i]; i++) {
            if(cmd[i] == 'R') {
                if(i && cmd[i-1] == 'R')
                    y++;
                g[y][i] = '/';
                if(cmd[i+1] == 'C')
                    y++;
            } else if(cmd[i] == 'F') {
                if(i && cmd[i-1] != 'R')
                    y--;
                g[y][i] = '\\';
            } else {
                g[y][i] = '_';
            }
            if(y > mx)  mx = y;
            if(y < mn)  mn = y;
        }
        len = i;
        for(i = mx; i >= mn; i--) {
            putchar('|'), j = 50;
            putchar(' ');
            while(!g[i][j]) j--;
            for(k = 0; k <= j; k++)
                printf("%c", !g[i][k] ? ' ' : g[i][k]);
            puts("");
        }
        putchar('+');
        for(i = -1; i <= len; i++)
            putchar('-');
        puts("\n");
    }
    return 0;
}
