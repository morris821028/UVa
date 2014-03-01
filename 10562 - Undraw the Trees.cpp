#include <stdio.h>
#include <string.h>
char g[205][205];
void dfs(int x, int y) {
    putchar(g[x][y]);
    putchar('(');
    x++;
    while(g[x][y] == '|')   x++;
    while(y >= 0 && g[x][y] == '-')   y--;
    y++;
    if(g[x][y] == '-') {
        while(g[x][y] == '-') {
            if(g[x+1][y] != ' ' && g[x+1][y] != 0)
                dfs(x+1, y);
            y++;
        }
    }
    putchar(')');
}
int main() {
    int t, i;
    scanf("%d", &t);
    while((i = getchar()) != '\n');
    while(t--) {
        memset(g, 0, sizeof(g));
        int n = 0;
        while(gets(g[n])) {
            if(g[n][0] == '#')  break;
            n++;
        }
        int root = -1;
        if(n > 0)
        for(i = 0; g[0][i]; i++) {
            if(g[0][i] != ' ') {
                root = i;
                break;
            }
        }
        putchar('(');
        if(root != -1)
            dfs(0, root);
        putchar(')');
        puts("");
    }
    return 0;
}
