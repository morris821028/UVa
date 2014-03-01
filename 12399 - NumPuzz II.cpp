#include <stdio.h>
int g[3][3], mn_step;
int btn_press[3][3];
char path[1024];
int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};
void press(int x, int y, int time) {
    static int i, tx, ty;
    for(i = 0; i < 5; i++) {
        tx = x+dx[i], ty = y+dy[i];
        if(tx < 0 || ty < 0 || tx >= 3 || ty >= 3)
            continue;
        g[tx][ty] -= time;
        if(g[tx][ty] < 0)
            g[tx][ty] += 10;
    }
}
void rpress(int x, int y, int time) {
    static int i, tx, ty;
    for(i = 0; i < 5; i++) {
        tx = x+dx[i], ty = y+dy[i];
        if(tx < 0 || ty < 0 || tx >= 3 || ty >= 3)
            continue;
        g[tx][ty] += time;
        if(g[tx][ty] > 9)
            g[tx][ty] -= 10;
    }
}
void dfs(int x, int y, int step) {
    if(step >= mn_step) return;
    if(y == 3)  x++, y = 0;
    int i, j, k;
    if(x == 3) {
        for(i = 0; i < 3; i++)
            if(g[2][i])
                return;
        mn_step = step;
        int idx = 0;
        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                for(k = 0; k < btn_press[i][j]; k++)
                    path[idx++] = i*3+j+'a';
            }
        }
        path[idx] = '\0';
        return;
    }
    if(x == 0) {
        for(i = 0; i < 10; i++) {
            press(x, y, i);
            btn_press[x][y] = i;
            dfs(x, y+1, step+i);
            rpress(x, y, i);
        }
    } else {
        if(g[x-1][y]) {
            j = g[x-1][y];
            press(x, y, j);
            btn_press[x][y] = j;
            dfs(x, y+1, step+j);
            rpress(x, y, j);
        } else {
            btn_press[x][y] = 0;
            dfs(x, y+1, step);
        }
    }
}
int main() {
    char dummy[256];
    int i, j;
    while(gets(dummy)) {
        for(i = 0; i < 3; i++)
            for(j = 0; j < 3; j++)
                scanf("%d", &g[i][j]);
        while(getchar() != '\n');
        mn_step = 0xffff;
        dfs(0, 0, 0);
        if(mn_step != 0xffff)
            puts(path);
        else
            puts("No solution.");
    }
    return 0;
}
