#include <stdio.h>
#include <string.h>
char g[15][15];
int ng[15][15], res;
void press(int x, int y) {
    ng[x][y] = !ng[x][y];
    if(x-1 >= 0)    ng[x-1][y] = !ng[x-1][y];
    if(x+1 < 10)    ng[x+1][y] = !ng[x+1][y];
    if(y-1 >= 0)    ng[x][y-1] = !ng[x][y-1];
    if(y+1 < 10)    ng[x][y+1] = !ng[x][y+1];
}
void dfs(int x, int y, int step) {
    if(y == 10)  x++, y = 0;
    if(step >= res) return;
    if(x == 0) {
        dfs(x, y+1, step);
        press(x, y);
        dfs(x, y+1, step+1);
        press(x, y);
    } else if(x < 10) {
        if(ng[x-1][y] == 1) {
            press(x, y);
            dfs(x, y+1, step+1);
            press(x, y);
        } else
            dfs(x, y+1, step);
    } else {
        int i;
        for(i = 0; i < 10; i++)
            if(ng[x-1][i])
                return;
        if(step < res)  res = step;
    }
}
int main() {
    char name[50];
    int i, j;
    while(gets(name)) {
        if(!strcmp(name, "end"))
            break;
        for(i = 0; i < 10; i++)
            gets(g[i]);
        for(i = 0; i < 10; i++) {
            for(j = 0; j < 10; j++) {
                ng[i][j] = g[i][j] == 'O';
            }
        }
        res = 0xffff;
        dfs(0, 0, 0);
        printf("%s %d\n", name, res);
    }
    return 0;
}
/*
all_off
##########
##########
##########
##########
##########
##########
##########
##########
##########
##########
all_on
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
OOOOOOOOOO
simple
#O########
OOO#######
#O########
####OO####
###O##O###
####OO####
##########
########O#
#######OOO
########O#
*/
