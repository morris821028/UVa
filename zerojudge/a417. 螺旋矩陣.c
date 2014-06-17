#include <stdio.h>

int main() {
    int t, n, m, op;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &op);
        m = n*n;
        int x = 0, y = 0, dirX, dirY, dir;
        int used[100][100] = {};
        int i = 1, j;
        if(op == 1) dirX = 0, dirY = 1, dir = 1;/*right*/
        else        dirX = 1, dirY = 0, dir = 2;/*down*/
        do {
            used[x][y] = i;
            x += dirX, y += dirY;
            if(x < 0 || y < 0 || x >= n || y >= n || used[x][y]) {
                x -= dirX, y -= dirY;
                if(op == 1) {
                    if(dir == 1)
                        dir++, dirX = 1, dirY = 0;
                    else if(dir == 2)
                        dir++, dirX = 0, dirY = -1;
                    else if(dir == 3)
                        dir++, dirX = -1, dirY = 0;
                    else
                        dir = 1, dirX = 0, dirY = 1;
                } else {
                    if(dir == 1)
                        dir = 4, dirX = -1, dirY = 0;
                    else if(dir == 2)
                        dir = 1, dirX = 0, dirY = 1;
                    else if(dir == 3)
                        dir = 2, dirX = 1, dirY = 0;
                    else
                        dir = 3, dirX = 0, dirY = -1;
                }
                x += dirX, y += dirY;
            }
            i++;
        } while(i <= m);
        for(i = 0; i < n; i++, puts("")) {
            for(j = 0; j < n; j++) {
                printf("%5d", used[i][j]);
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
