#include <stdio.h>
char map[100][100];
void dfs(int x, int y) {
    if(map[x][y] == 'X' || map[x][y] == '#')
        return ;
    map[x][y] = '#';
    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
}
int main() {
    int t, i, j;
    scanf("%d ", &t);
    while(t--) {
        int n = 0;
        while(gets(map[n])) {
            if(map[n][0] == '_')
                break;
            n++;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; map[i][j]; j++) {
                if(map[i][j] == '*')
                    dfs(i, j);
            }
        }
        for(i = 0; i <= n; i++)
            puts(map[i]);
    }
    return 0;
}
