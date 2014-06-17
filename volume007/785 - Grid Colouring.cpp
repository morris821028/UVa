#include <stdio.h>
#include <string.h>
int used[40][100] = {};
char g[40][100];
void dfs(int i, int j, char color) {
    if(used[i][j])  return;
    if(g[i][j] == 'X')  return;
    used[i][j] = 1, g[i][j] = color;
    dfs(i+1, j, color);
    dfs(i-1, j, color);
    dfs(i, j+1, color);
    dfs(i, j-1, color);
}
int main() {
    while(1) {
        int n = 0;
        while(1) {
            if(!gets(g[n]))
                return 0;
            if(g[n][0] == '_')  break;
            n++;
        }
        memset(used, 0, sizeof(used));
        int i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; g[i][j]; j++) {
                if(g[i][j] != 'X' && g[i][j] != ' ') {
                    if(used[i][j])  continue;
                    dfs(i, j, g[i][j]);
                }
            }
        }
        for(i = 0; i < n; i++)
            puts(g[i]);
        puts("_____________________________");
    }
    return 0;
}
