#include <stdio.h>
#include <string.h>
char g[105][105];
int used[105][105];
int n, m;
void dfs(int x, int y, int label, int v) {
    if(x < 0 || y < 0 || x >= n || y >= m)
        return;
    if(g[x][y] != v || used[x][y])
        return;
    used[x][y] = label;
    dfs(x+1, y-1, label, v);
    dfs(x+1, y, label, v);
    dfs(x+1, y+1, label, v);
    dfs(x-1, y-1, label, v);
    dfs(x-1, y, label, v);
    dfs(x-1, y+1, label, v);
    dfs(x, y+1, label, v);
    dfs(x, y-1, label, v);
}
int main() {
    char s[1024];
    while(true) {
        n = 0, m;
        memset(used, 0, sizeof(used));
        int i, j, k, label = 0;
        while(gets(s)) {
            if(s[0] == '%')
                break;
            m = 0;
            for(i = 0; s[i]; i++) {
                if(s[i] != ' ')
                    g[n][m++] = s[i];
            }
            n++;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(used[i][j] == 0) {
                    label++;
                    dfs(i, j, label, g[i][j]);
                }
            }
        }
        int align[105] = {};
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++) {
                int tmp = used[j][i], cnt = 0;
                while(tmp)
                    tmp = tmp/10, cnt++;
                if(align[i] < cnt)
                    align[i] = cnt;
            }
        }
        char format[50] = "%?d";
        for(i = 0; i < n; i++, puts("")) {
            for(j = 0; j < m; j++) {
                format[1] = align[j]+'0';
                if(j)
                    putchar(' ');
                printf(format, used[i][j]);
            }
        }
        puts("%");
        if(s[0] != '%')
            break;
    }
    return 0;
}
