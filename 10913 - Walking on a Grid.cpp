#include <stdio.h>
#include <queue>
using namespace std;
int N, K;
int dp[80][80][10][3];//up, left, right
int inq[80][80][10][3];
int g[80][80];
void spfa() {
    int i, j, k, l;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            for(k = 0; k <= K; k++) {
                for(l = 0; l < 3; l++)
                    dp[i][j][k][l] = -0xfffffff;
            }
        }
    }
    queue<int> X, Y, NEG, DIR;
    int x, y, neg, dir;
    int tx, ty, tneg, tdir;
    X.push(0), Y.push(0), NEG.push(g[0][0] < 0), DIR.push(0);
    dp[0][0][g[0][0] < 0][0] = g[0][0];
    while(!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        neg = NEG.front(), NEG.pop();
        dir = DIR.front(), DIR.pop();
        inq[x][y][neg][dir] = 0;
        tx = x, ty = y-1, tdir = 1, tneg = neg;
        if(dir != 2 && ty >= 0) { // left
            if(g[tx][ty] < 0)   tneg = neg+1;
            if(tneg <= K && dp[tx][ty][tneg][tdir] < dp[x][y][neg][dir]+g[tx][ty]) {
                dp[tx][ty][tneg][tdir] = dp[x][y][neg][dir]+g[tx][ty];
                if(inq[tx][ty][tneg][tdir] == 0) {
                    inq[tx][ty][tneg][tdir] = 1;
                    X.push(tx), Y.push(ty), NEG.push(tneg), DIR.push(tdir);
                }
            }
        }
        tx = x, ty = y+1, tdir = 2, tneg = neg;
        if(dir != 1 && ty < N) { // right
            if(g[tx][ty] < 0)   tneg = neg+1;
            if(tneg <= K && dp[tx][ty][tneg][tdir] < dp[x][y][neg][dir]+g[tx][ty]) {
                dp[tx][ty][tneg][tdir] = dp[x][y][neg][dir]+g[tx][ty];
                if(inq[tx][ty][tneg][tdir] == 0) {
                    inq[tx][ty][tneg][tdir] = 1;
                    X.push(tx), Y.push(ty), NEG.push(tneg), DIR.push(tdir);
                }
            }
        }
        tx = x+1, ty = y, tdir = 0, tneg = neg;
        if(tx < N) { // up
            if(g[tx][ty] < 0)   tneg = neg+1;
            if(tneg <= K && dp[tx][ty][tneg][tdir] < dp[x][y][neg][dir]+g[tx][ty]) {
                dp[tx][ty][tneg][tdir] = dp[x][y][neg][dir]+g[tx][ty];
                if(inq[tx][ty][tneg][tdir] == 0) {
                    inq[tx][ty][tneg][tdir] = 1;
                    X.push(tx), Y.push(ty), NEG.push(tneg), DIR.push(tdir);
                }
            }
        }
    }
    int ret = -0xfffffff;
    for(i = 0; i <= K; i++)
        for(j = 0;j < 3; j++)
            ret = max(ret, dp[N-1][N-1][i][j]);
    if(ret != -0xfffffff)
        printf("%d\n", ret);
    else
        puts("impossible");
}
int main() {
    int i, j, cases = 0;
    while(scanf("%d %d", &N, &K) == 2) {
        if(N == 0)
            break;
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                scanf("%d", &g[i][j]);
        printf("Case %d: ", ++cases);
        spfa();
    }
    return 0;
}
