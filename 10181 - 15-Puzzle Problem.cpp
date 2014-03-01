#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define LLU unsigned long long
using namespace std;
struct status {
    char board[4][4];
    int ix, iy;
} init;
int pos[16][2], mxdep;
int dir[4][2] = {{0,-1},{-1,0},{1,0},{0,1}};/*u,l,r,d*/
char dirc[4] = {'L', 'U', 'D', 'R'}, path[100];
int solved;
bool solvable() {
    int sum = 0, row, i, j;
    for(i = 0; i < 16; i++) {
        if(init.board[i/4][i%4] == 0) {
            row = i/4 + 1;
            continue;
        }
        for(j = i+1; j < 16; j++) {
            if(init.board[j/4][j%4] < init.board[i/4][i%4]) {
                if(init.board[j/4][j%4])
                    sum++;
            }
        }
    }
    return 1-(sum+row)%2;
}
int H() {
    static int i, j, sum, num;
    sum = 0;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            num = init.board[i][j];
            if(num == 0)
                continue;
            sum += abs(i-pos[num][0]) + abs(j-pos[num][1]);
        }
    }
    return sum;
}
int Htable[4][4][16];
int IDA(int dep, int hv, int prestep) {
    if(hv == 0) {
        solved = dep;
        path[dep] = '\0';
        puts(path);
        return dep;
    }
    if(dep + 5*hv/3 > mxdep) {
        return dep + 5*hv/3;
    }
    int i, tx, ty, x = init.ix, y = init.iy;
    int submxdep = 0xfff, val = 0xfff, shv;

    for(i = 0; i < 4; i++) {
        if(i + prestep == 3)    continue;
        tx = x + dir[i][0], ty = y + dir[i][1];
        if(tx < 0 || ty < 0 || tx > 3 || ty > 3)
            continue;

        shv = hv;
        shv -= Htable[tx][ty][init.board[tx][ty]];
        shv += Htable[x][y][init.board[tx][ty]];
        init.ix = tx, init.iy = ty;
        swap(init.board[x][y], init.board[tx][ty]);

        path[dep] = dirc[i];
        val = IDA(dep+1, shv, i);

        swap(init.board[x][y], init.board[tx][ty]);
        init.ix = x, init.iy = y;
        if(solved)  return solved;
        submxdep = min(submxdep, val);
    }
    return submxdep;
}
int main() {
    int test, i, j, k, initH;
    int cases = 0;
    for(i = 0, k = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            pos[++k][0] = i, pos[k][1] = j;
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            for(k = 1; k < 16; k++)
                Htable[i][j][k] = abs(i - pos[k][0]) + abs(j - pos[k][1]);
    scanf("%d", &test);
    while(test--) {
        cases++;
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                scanf("%d", &k);
                init.board[i][j] = k;
                if(init.board[i][j] == 0) {
                    init.ix = i, init.iy = j;
                }
            }
        }
        if(solvable()) {
            solved = 0, initH = mxdep = H();
            if(!mxdep) {
                puts("");
                continue;
            }
            while(solved == 0)
                mxdep = IDA(0, initH, -1);
            //printf("%d\n", solved);
        }else {
            puts("This puzzle is not solvable.");
        }
    }
    return 0;
}
/*
2
6 2 8 4
12 14 1 10
13 15 3 9
11 0 5 7
0 1 3 8
5 7 4 6
9 2 10 11
13 14 15 12
*/
