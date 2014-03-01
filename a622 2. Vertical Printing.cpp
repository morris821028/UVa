#include <stdio.h>
#include <string.h>

int main() {
    char g[105][105], cmd[105];
    int n = 0, i, j, mx = 0;
    memset(g, ' ', sizeof(g));
    while(gets(cmd) && strcmp(cmd, "END")) {
        for(i = 0; cmd[i]; i++)
            g[i][n] = cmd[i];
        n += 3;
        mx = mx > i ? mx : i;
    }
    for(i = 0; i < mx; i++) {
        j = 100;
        while(j >= 0 && g[i][j] == ' ')
            j--;
        g[i][j+1] = '\0';
        puts(g[i]);
    }
    return 0;
}
