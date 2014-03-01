#include <stdio.h>
#include <queue>
using namespace std;
char g[105][105];
int dis[105][105][4], inq[105][105][4]; //[pointX][pointY][prevDir]
int n, m, d[105][105];
int dx[] = {1,0,0,-1};// to N, E, W, S
int dy[] = {0,-1,1,0};
void spfa() {
    int i, j, k, x, y, r, tx, ty, rx, ry;
    int cost;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            for(k = 0; k < 4; k++)
                dis[i][j][k] = 0xfffffff, inq[i][j][k] = 0;
    queue<int> X, Y, R;
    X.push(n-1), Y.push(0), R.push(0);
    dis[n-1][0][0] = 0;
    while(!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        r = R.front(), R.pop();
        inq[x][y][r] = 0;
        if(g[x][y] == '.') {
            for(i = 0; i < 4; i++) {
                tx = x+dx[i], ty = y+dy[i];
                if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if(g[tx][ty] == '#')    continue;
                bool updateFlag = false;
                if(g[tx][ty] == '.')
                    updateFlag = true;
                if(g[tx][ty] == 'N' && i == 0)
                    updateFlag = true;
                if(g[tx][ty] == 'E' && i == 1)
                    updateFlag = true;
                if(g[tx][ty] == 'W' && i == 2)
                    updateFlag = true;
                if(g[tx][ty] == 'S' && i == 3)
                    updateFlag = true;
                if(updateFlag == true) {
                    if(dis[tx][ty][i] > dis[x][y][r]+1) {
                        dis[tx][ty][i] = dis[x][y][r]+1;
                        if(inq[tx][ty][i] == 0) {
                            inq[tx][ty][i] = 1;
                            X.push(tx), Y.push(ty), R.push(i);
                        }
                    }
                }
            }
        } else {// rotate door
            for(i = 0; i < 4; i++) {
                tx = x+dx[i], ty = y+dy[i];
                if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if(g[tx][ty] == '#')    continue;
                if(i+r == 3 || i == r)
                    cost = 2*d[x][y];
                else
                    cost = d[x][y];
                bool updateFlag = false;
                if(g[tx][ty] == '.')
                    updateFlag = true;
                if(g[tx][ty] == 'N' && i == 0)
                    updateFlag = true;
                if(g[tx][ty] == 'E' && i == 1)
                    updateFlag = true;
                if(g[tx][ty] == 'W' && i == 2)
                    updateFlag = true;
                if(g[tx][ty] == 'S' && i == 3)
                    updateFlag = true;
                if(updateFlag == true) {
                    if(dis[tx][ty][i] > dis[x][y][r]+1+cost) {
                        dis[tx][ty][i] = dis[x][y][r]+1+cost;
                        if(inq[tx][ty][i] == 0) {
                            inq[tx][ty][i] = 1;
                            X.push(tx), Y.push(ty), R.push(i);
                        }
                    }
                }
            }
        }
    }
    int ret = dis[0][m-1][0];
    for(i = 0; i < 4; i++)
        ret = min(ret, dis[0][m-1][i]);
    if(ret == 0xfffffff)
        puts("Poor Kianoosh");
    else
        printf("%d\n", ret);
}
int main() {
    int test, i, j;
    scanf("%d", &test);
    while(test--) {
        scanf("%d %d", &n, &m);
        while(getchar() != '\n');
        for(i = 0; i < n; i++)
            gets(g[i]);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] != '.' && g[i][j] !='#')
                    scanf("%d", &d[i][j]);
            }
        }
        spfa();
    }
    return 0;
}
/*
Input:
1
3 3
.#.
..W
...
10

Output:
14
*/
