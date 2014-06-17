#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, sx, sy;
    char D[2], cmd[1000], pre[100][100] = {};
    scanf("%d %d", &n, &m);
    while(scanf("%d %d %s", &sx, &sy, D) == 3) {
        scanf("%s", cmd);
        int d = D[0], flag = 0, i;
        for(i = 0; cmd[i]; i++) {
            if(cmd[i] == 'F') {
                switch(d) {
                    case 'N':sy++;break;
                    case 'E':sx++;break;
                    case 'W':sx--;break;
                    case 'S':sy--;break;
                }
            } else if(cmd[i] == 'R') {
                switch(d) {
                    case 'N':d = 'E';break;
                    case 'E':d = 'S';break;
                    case 'W':d = 'N';break;
                    case 'S':d = 'W';break;
                }
            } else {
                switch(d) {
                    case 'N':d = 'W';break;
                    case 'E':d = 'N';break;
                    case 'W':d = 'S';break;
                    case 'S':d = 'E';break;
                }
            }
            if(sx < 0 || sy < 0 || sx > n || sy > m) {
                switch(d) {
                    case 'N':sy--;break;
                    case 'E':sx--;break;
                    case 'W':sx++;break;
                    case 'S':sy++;break;
                }
                if(pre[sx][sy] == 1)
                    continue;
                flag = 1;
                pre[sx][sy] = 1;
                break;
            }
        }
        if(!flag)
            printf("%d %d %c\n", sx, sy, d);
        else {
            printf("%d %d %c LOST\n", sx, sy, d);
        }
    }
    return 0;
}
