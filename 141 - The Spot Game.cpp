#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
void rotate(int x[][50], int n) {
    int y[50][50], i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            y[j][n-i-1] = x[i][j];
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            x[i][j] = y[i][j];
}
int main() {
    int n;
    while(scanf("%d", &n), n) {
        map<string, int> r;
        int m = 2*n, board[50][50] = {}, x, y;
        int flag = -1, move;
        char cmd[3];
        for(int i = 0; i < m; i++) {
            scanf("%d %d %s", &x, &y, cmd);
            if(flag != -1)  continue;
            x--, y--;
            if(cmd[0] == '+')
                board[x][y] = 1;
            else    board[x][y] = 0;
            string s = "";
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                    s += (board[j][k]+'0');
            if(r[s] == 1) {
                flag = i&1;
                move = i;
                continue;
            }
            for(int rr = 0; rr < 4; rr++) {
                string s = "";
                for(int j = 0; j < n; j++)
                    for(int k = 0; k < n; k++)
                        s += (board[j][k]+'0');
                r[s] = 1;
                rotate(board, n);
            }
        }
        if(flag == -1)
            puts("Draw");
        else
            printf("Player %d wins on move %d\n", !flag+1, move+1);
    }
    return 0;
}
