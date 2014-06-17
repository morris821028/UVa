#include <stdio.h>
#include <string.h>
char g[105][105], used[105][105];
int n, m, res;
void dfs(int x, int y) {
    if(x < 0 || y < 0 || x >= n || y >= m)
        return;
    if(g[x][y] == '1' || used[x][y])
        return;
    used[x][y] = 1;
    res++;
    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
}
int main() {
    int t, x, y;
    scanf("%d", &t);
    while(getchar() != '\n');
    gets(g[0]);
    while(t--) {
        gets(g[0]);
        memset(used, 0, sizeof(used));
        sscanf(g[0], "%d %d", &x, &y);
        n = 0, m;
        while(gets(g[n]) && g[n][0])
            n++;
        m = strlen(g[0]);
        res = 0;
        dfs(x-1, y-1);
        printf("%d\n", res);
        if(t)
            puts("");
    }
    return 0;
}
/*
1

02 01
1001101
0011111
0001001
1100011
1111111
1100110
1110111
*/
