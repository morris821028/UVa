#include <stdio.h>
#include <string.h>
int main() {
    char cmd[100], g[300][300], co, name[100];
    int n, m, i, j, x, y, z, w;
    while(gets(cmd)) {
        if(cmd[0] == 'X')   break;
        if(cmd[0] == 'I') {
            sscanf(cmd+1, "%d %d", &m, &n);
            for(i = 0; i < n; i++)
                for(j = 0; j < m; j++)
                    g[i][j] = 'O';
        } else if(cmd[0] == 'C') {
            for(i = 0; i < n; i++)
                for(j = 0; j < m; j++)
                    g[i][j] = 'O';
        } else if(cmd[0] == 'L') {
            sscanf(cmd+1, "%d %d", &y, &x);
            co = cmd[strlen(cmd)-1];
            g[x-1][y-1] = co;
        } else if(cmd[0] == 'V') {
            sscanf(cmd+1, "%d %d %d", &x, &y, &z);
            if(y > z) {int tmp = y; y = z, z = tmp;}
            co = cmd[strlen(cmd)-1];
            for(i = y-1; i <= z-1; i++)
                g[i][x-1] = co;
        } else if(cmd[0] == 'H') {
            sscanf(cmd+1, "%d %d %d", &x, &y, &z);
            if(x > y) {int tmp = x; x = y, y = tmp;}
            co = cmd[strlen(cmd)-1];
            for(i = x-1; i <= y-1; i++)
                g[z-1][i] = co;
        } else if(cmd[0] == 'K') {
            sscanf(cmd+1, "%d %d %d %d", &x, &y, &z, &w);
            co = cmd[strlen(cmd)-1];
            for(i = x-1; i <= z-1; i++)
                for(j = y-1; j <= w-1; j++)
                    g[j][i] = co;
        } else if(cmd[0] == 'F') {
            sscanf(cmd+1, "%d %d", &y, &x);
            co = cmd[strlen(cmd)-1];
            char prev = g[x-1][y-1];
            int Q[70000][2], qt = 0, used[300][300] = {};
            g[x-1][y-1] = co;
            Q[0][0] = x-1, Q[0][1] = y-1;
            for(i = 0; i <= qt; i++) {
                x = Q[i][0], y = Q[i][1];
                if(x+1 < n && g[x+1][y] == prev && !used[x+1][y])
                    Q[++qt][0] = x+1, Q[qt][1] = y, g[x+1][y] = co, used[x+1][y] = 1;

                if(x-1 >= 0 && g[x-1][y] == prev && !used[x-1][y])
                    Q[++qt][0] = x-1, Q[qt][1] = y, g[x-1][y] = co, used[x-1][y] = 1;

                if(y+1 < m && g[x][y+1] == prev && !used[x][y+1])
                    Q[++qt][0] = x, Q[qt][1] = y+1, g[x][y+1] = co, used[x][y+1] = 1;

                if(y-1 >= 0 && g[x][y-1] == prev && !used[x][y-1])
                    Q[++qt][0] = x, Q[qt][1] = y-1, g[x][y-1] = co, used[x][y-1] = 1;

            }
        } else if(cmd[0] == 'S') {
            sscanf(cmd+1, "%s", name);
            puts(name);
            for(i = 0; i < n; i++, puts(""))
                for(j = 0; j < m; j++)
                    putchar(g[i][j]);
        }
    }
    return 0;
}
