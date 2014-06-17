#include <stdio.h>
#include <string.h>
char g[10][10];
char used[10][10];
int dfs(int i, int j) {
    if(i < 0 || j < 0 || i >= 9 || j >= 9)
        return 0;
    if(g[i][j] == 'O')  return 1;
    if(g[i][j] == 'X')  return 2;
    if(used[i][j])  return 0;
    int flag = 0;
    used[i][j] = 1;
    flag |= dfs(i+1, j);
    flag |= dfs(i-1, j);
    flag |= dfs(i, j+1);
    flag |= dfs(i, j-1);
    return flag;
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 9; i++)
            scanf("%s", g[i]);
        int w = 0, b = 0;
        for(i = 0; i < 9; i++) {
            for(j = 0; j < 9; j++) {
                if(g[i][j] == '.') {
                    memset(used, 0, sizeof(used));
                    int flag = dfs(i, j);
                    if(flag == 1)   w++;
                    if(flag == 2)   b++;
                } else if(g[i][j] == 'O')
                    w++;
                else    b++;
            }
        }
        printf("Black %d White %d\n", b, w);
    }
    return 0;
}
