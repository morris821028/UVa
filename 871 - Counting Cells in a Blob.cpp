#include <stdio.h>
#include <string.h>
int used[35][35], cnt = 0;
int n;
char g[35][35];
void dfs(int i, int j) {
    if(i >= n || i < 0 || j < 0)
        return;
    if(g[i][j] != '1' || used[i][j])  return;
    cnt++;
    used[i][j] = 1;
    dfs(i+1, j);
    dfs(i+1, j-1);
    dfs(i+1, j+1);
    dfs(i-1, j);
    dfs(i-1, j+1);
    dfs(i-1, j-1);
    dfs(i, j+1);
    dfs(i, j-1);
}
int main() {
    int t;
    scanf("%d", &t);
    gets(g[0]);
    gets(g[0]);
    while(t--) {
        n = 0;
        memset(g, 0, sizeof(g));
        while(gets(g[n])) {
            if(g[n][0] == '\0') break;
            n++;
        }
        memset(used, 0, sizeof(used));
        int ans = 0, i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; g[i][j]; j++) {
                if(used[i][j] == 0 && g[i][j] == '1') {
                    cnt = 0;
                    dfs(i, j);
                    if(cnt > ans)
                        ans = cnt;
                }
            }
        }
        printf("%d\n", ans);
        if(t)
            puts("");
    }
    return 0;
}
/*
1

11000
01100
00101
10001
01011
*/
