#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
int g[8][8], g2[8][8][4]; // up, down, left, right
int dir[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};
char wdir[5] = "NSWE";
int dp[8][8], stp[8][8];
int sx, sy, ex, ey;
int i, j, x1, x2, y1, y2;
void backtrack(int i, int j) {
    if(dp[i][j] == 1)   return;
    if(stp[i][j] == 0) {
        backtrack(i, j+1);
        putchar('N');
    } else if(stp[i][j] == 1) {
        backtrack(i, j-1);
        putchar('S');
    } else if(stp[i][j] == 2) {
        backtrack(i+1, j);
        putchar('W');
    } else {
        backtrack(i-1, j);
        putchar('E');
    }
}
void sol() {
    memset(dp, 0, sizeof(dp));
    memset(stp, 0, sizeof(stp));
    queue<int> X, Y;
    dp[sx][sy] = 1;
    X.push(sx), Y.push(sy);
    while(!X.empty()) {
        sx = X.front(), X.pop();
        sy = Y.front(), Y.pop();
        for(i = 0; i < 4; i++) {
            x1 = sx+dir[i][0], y1 = sy+dir[i][1];
            if(g2[sx][sy][i])  continue;
            if(x1 < 1 || x1 > 6 || y1 < 1 || y1 > 6)
                continue;
            if(dp[x1][y1])      continue;
            dp[x1][y1] = dp[sx][sy]+1;
            stp[x1][y1] = i;
            X.push(x1), Y.push(y1);
        }
    }
    /*for(i = 1; i <= 6; i++, puts(""))
        for(j = 1; j <= 6; j++)
            printf("%d ", dp[i][j]);*/
    backtrack(ex, ey);
    puts("");
}
int main() {
    while(scanf("%d %d", &sx, &sy) == 2) {
        if(!sx && !sy)  break;
        scanf("%d %d", &ex, &ey);
        memset(g, 0, sizeof(g));
        memset(g2, 0, sizeof(g2));
        for(i = 0; i < 3; i++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            if(x1 == x2) {
                for(j = y1; j < y2; j++)
                    g2[x1][j+1][3] = 1;
                if(x1+1 <= 6)
                for(j = y1; j < y2; j++)
                    g2[x1+1][j+1][2] = 1;
            } else {
                for(j = x1; j < x2; j++)
                    g2[j+1][y1][1] = 1;
                if(y1+1 <= 6)
                for(j = x1; j < x2; j++)
                    g2[j+1][y1+1][0] = 1;
            }
        }
        /*for(i = 1; i <= 6; i++, puts(""))
            for(j = 1; j <= 6; j++)
                printf("(%d%d%d%d)", g2[i][j][0], g2[i][j][1], g2[i][j][2], g2[i][j][3]);*/
        sol();
    }
    return 0;
}
/*
1 6
2 6
0 0 1 0
1 5 1 6
1 5 3 5
0 0
*/
