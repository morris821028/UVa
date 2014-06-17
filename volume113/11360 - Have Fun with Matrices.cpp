#include <stdio.h>
#include <string.h>

int main() {
    int t, n, m, i, j;
    int cases = 0;
    int map[20][20];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                scanf("%1d", &map[i][j]);
        }
        scanf("%d", &m);
        char cmd[150];
        while(m--) {
            scanf("%s", cmd);
            if(!strcmp(cmd, "transpose")) {
                for(i = 0; i < n; i++) {
                    for(j = i+1; j < n; j++) {
                        int tmp;
                        tmp = map[i][j], map[i][j] = map[j][i], map[j][i] = tmp;
                    }
                }
            } else if(!strcmp(cmd, "inc")) {
                for(i = 0; i < n; i++)
                    for(j = 0; j < n; j++) {
                        map[i][j] = map[i][j]+1;
                        if(map[i][j] == 10)
                            map[i][j] = 0;
                    }
            } else if(!strcmp(cmd, "dec")) {
                for(i = 0; i < n; i++)
                    for(j = 0; j < n; j++) {
                        map[i][j] = (map[i][j]+9)%10;
                        if(map[i][j] < 0)
                            map[i][j] = 9;
                    }
            } else {
                int a, b;
                scanf("%d %d", &a, &b);
                a--, b--;
                if(!strcmp(cmd, "col")) {
                    for(i = 0; i < n; i++) {
                        int tmp;
                        tmp = map[i][a], map[i][a] = map[i][b], map[i][b] = tmp;
                    }
                } else {
                    for(i = 0; i < n; i++) {
                        int tmp;
                        tmp = map[a][i], map[a][i] = map[b][i], map[b][i] = tmp;
                    }
                }
            }
        }
        printf("Case #%d\n", ++cases);
        for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < n; j++)
                printf("%d", map[i][j]);
        puts("");
    }
    return 0;
}
