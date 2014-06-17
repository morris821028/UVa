#include <stdio.h>
#include <string.h>
int n, m, x, y;
char s[3], g[20][20], used[20][20];
int color(int x, int y) {
    if(x < 0 || y < 0 || x >= n || y >= m)
        return 0;
    if(used[x][y] == 1) return 0;
    used[x][y] = 1;
    return 1;
}
int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}, move;
void dfs(int x, int y) {
    int i, tx, ty;
    move++;
    for(i = 0; i < 4; i++) {
        tx = x+dir[i][0], ty = y+dir[i][1];
        if(color(tx, ty) == 1 && g[tx][ty] == '0') {
            dfs(tx, ty);
            break;
        }

    }
    color(x+1, y);
    color(x-1, y);
    color(x, y+1);
    color(x, y-1);
}
void printLine(int n) {
    int i;
    putchar('|');
    for(i = 0; i < n; i++) {
        putchar('-');
        putchar('-');
        putchar('-');
        putchar('|');
    }
    puts("");
}
int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        scanf("%d %d", &x, &y);
        memset(used, 0, sizeof(used));
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%s", s);
                g[i][j] = s[0];
            }
        }
        x--, y--;
        used[x][y] = 1;
        move = 0;
        dfs(x, y);
        puts("");
        for(i = 0; i < n; i++) {
            printLine(m);
            putchar('|');
            for(j = 0; j < m; j++) {
                putchar(' ');
                if(used[i][j])
                    putchar(g[i][j]);
                else
                    putchar('?');
                putchar(' ');
                putchar('|');
            }
            puts("");
        }
        printLine(m);
        puts("");
        printf("NUMBER OF MOVEMENTS: %d\n", move-1);

    }
    return 0;
}
