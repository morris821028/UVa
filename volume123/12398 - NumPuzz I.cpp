#include <stdio.h>
#include <string.h>
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};
int g[3][3];
void color(int x, int y) {
    int i, tx, ty;
    for(i = 0; i < 5; i++) {
        tx = x+dx[i];
        ty = y+dy[i];
        if(tx < 0 || ty < 0 || tx >= 3 || ty >= 3)
            continue;
        g[tx][ty]++;
    }
}
int main() {
    char s[512];
    int cases = 0, i, j, v;
    while(gets(s)) {
        memset(g, 0, sizeof(g));
        for(i = 0; s[i]; i++) {
            v = s[i]-'a';
            color(v/3, v%3);
        }
        printf("Case #%d:\n", ++cases);
        for(i = 0; i < 3; i++, puts("")) {
            for(j = 0; j < 3; j++) {
                if(j)   putchar(' ');
                printf("%d", g[i][j]%10);
            }
        }

    }
    return 0;
}
