#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c, s, i, j;
    while(scanf("%d %d %d", &r, &c, &s) == 3) {
        if(r == 0 && c == 0 && s == 0)
            break;
        char map[20][20];
        for(i = 0; i < r; i++)
            scanf("%s", map[i]);
        int used[20][20] = {};
        int x = 0, y = s-1, step = 0;
        for(i = 0; i < r; i++)
            for(j = 0; j < c; j++)
                used[i][j] = -1;
        used[x][y] = 0;
        while(1) {
            step++;
            if(map[x][y] == 'N')
                x--;
            else if(map[x][y] == 'S')
                x++;
            else if(map[x][y] == 'E')
                y++;
            else
                y--;
            if(x < 0 || y < 0 || x >= r || y >= c) {
                printf("%d step(s) to exit\n", step);
                break;
            }
            if(used[x][y] != -1) {
                printf("%d step(s) before a loop of %d step(s)\n", used[x][y], step-used[x][y]);
                break;
            }
            used[x][y] = step;
        }
    }
    return 0;
}
