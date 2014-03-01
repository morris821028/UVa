#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
char g[512][512], used[512];
int path[512], buf[512], plen, n, i, j, x, y, p, q;
void solH() {
    path[0] = 1, plen = 1, used[1] = 1;
    for(i = 2; i <= n; i++) {
        if(g[1][i]) {
            plen = 2;
            path[1] = i;
            used[i] = 1;
            break;
        }
    }
    int ispath = 1, update;
    do {
        update = 0;
        if(ispath) {
            for(i = 1, j = 0; i < plen; j = i++) {
                if(g[path[j]][path[plen-1]] && g[path[i]][path[0]]) {
                    for(p = i, q = plen-1; p < q; p++, q--)
                        swap(path[p], path[q]);
                    path[plen++] = path[0];
                    ispath = 0;
                    update = 1;
                    break;
                }
            }
        } else {
            for(i = 1; i < plen; i++) {
                for(j = 1; j <= n; j++) {
                    if(g[path[i]][j] && !used[j]) {
                        buf[p = 0] = j;
                        for(q = i; q < plen; q++)
                            buf[++p] = path[q];
                        for(q = plen-1; q > i; q--)
                            buf[++p] = path[q];
                        for(q = 0; q <= p; q++)
                            path[q] = buf[q];
                        ispath = 1;
                        update = 1;
                        used[j] = 1;
                        i = plen+10;
                        j = n+1;
                        break;
                    }
                }
            }
        }
        if(update == 0 && ispath) {
            for(i = 1; i <= n; i++) {
                if(g[path[plen-1]][i] && used[i] == 0) {
                    path[plen++] = i;
                    used[i] = 1;
                    update = 1;
                    break;
                }
            }
        }
    } while(update);
    if(!ispath && plen == n+1) {
        for(i = 0; i < plen; i++)
            printf("%d%c", path[i], i == plen-1 ? '\n' : ' ');
    } else
        puts("N");
}
int main() {
    char s[500];
    while(scanf("%d", &n) == 1) {
        memset(g, 0, sizeof(g));
        memset(used, 0, sizeof(used));
        while(getchar() != '\n');
        while(gets(s) && s[0] != '%') {
            sscanf(s, "%d %d", &x, &y);
            if(x == y)  continue;
            if(x > n || y > n)
                continue;
            g[x][y] = g[y][x] = 1;
        }
        solH();
    }
    return 0;
}
