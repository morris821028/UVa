#include <stdio.h>

int main() {
    char map[9][9] = {};
    int n;
    int i, j, a, b, x, y;
    while(scanf("%s", &map[0]) == 1) {
        for(i = 1; i < 8; i++) {
            scanf("%s", map[i]);
        }
        scanf("%d", &n);
        for(i = 0; i < 8; i++) {
            for(j = 0; j < 8; j++) {
                map[i][j] -= 48;
            }
        }
        while(n--) {
            char next[10][10] = {};
            for(i = 0; i < 8; i++) {
                for(j = 0; j < 8; j++) {
                    int cnt = 0;
                    for(a = -1; a <= 1; a++) {
                        for(b = -1; b <= 1; b++) {
                            if(a == 0 && b == 0)
                                continue;
                            x = i+a, y = j+b;
                            if(x < 0 || x >= 8 || y < 0 || y >= 8)
                                continue;
                            cnt += map[x][y];
                        }
                    }
                    if(map[i][j] == 1) {
                        if(cnt == 2 || cnt == 3)
                            next[i][j] = 1;
                        else
                            next[i][j] = 0;
                    } else {
                        if(cnt == 3)
                            next[i][j] = 1;
                        else
                            next[i][j] = 0;
                    }
                }
            }
            for(i = 0; i < 8; i++) {
                for(j = 0; j < 8; j++) {
                    map[i][j] = next[i][j];
                }
            }
        }
        for(i = 0; i < 8; i++, puts(""))
            for(j = 0; j < 8; j++)
                printf("%d", map[i][j]);
    }
    return 0;
}
