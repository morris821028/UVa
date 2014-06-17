#include <stdio.h>
#include <string.h>

char map[105][105], used[105][105];
int ans;
void dfs(int x, int y) {
    if(x < 0 || y < 0 || map[x][y] == 0)
        return;
    if(used[x][y] != 0 || map[x][y] != 'W')
        return;
    used[x][y] = 1;
    ans++;
    int i, j;
    for(i = -1; i <= 1; i++)
        for(j = -1; j <= 1; j++)
            dfs(x+i, y+j);
}
int main() {
    int t, i, j;
    char str[105];
    scanf("%d ", &t);
    while(t--) {
        memset(map, 0, sizeof(map));
        int n = 0;
        while(gets(str)) {
            if(str[0] == '\0')
                break;
            if(str[0] != 'W' && str[0] != 'L') {
                sscanf(str, "%d %d", &i, &j);
                memset(used, 0, sizeof(used));
                ans = 0;
                dfs(i-1, j-1);
                printf("%d\n", ans);
            } else {
                sscanf(str, "%s", map[n]);
                n++;
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
