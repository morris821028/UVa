#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
// He always starts his ride facing north
int dp[30][30][4][5]; //[x][y][dir][color]
char g[30][30];
int n, m, sx, sy, ex, ey;
struct Node {
    int x, y, dir, color, step;
    Node(int a, int b, int c, int d, int e):
        x(a), y(b), dir(c), color(d), step(e) {}
};
void sol() {
    memset(dp, 0, sizeof(dp));
    dp[sx][sy][0][0] = 1;
    queue<Node> Q;
    Q.push(Node(sx, sy, 0, 0, 0));
    Node tn(0,0,0,0,0);
    int ret = -1, tx, ty;
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        if(tn.x == ex && tn.y == ey && tn.color == 0) {
            ret = tn.step;
            break;
        }
        // next
        tx = tn.x + dx[tn.dir], ty = tn.y + dy[tn.dir];
        if(tx < 0 || ty < 0 || tx >= n || ty >= m || g[tx][ty] == '#')
            {}
        else {
            if(dp[tx][ty][tn.dir][(tn.color+1)%5] == 0) {
                dp[tx][ty][tn.dir][(tn.color+1)%5] = tn.step+1;
                Q.push(Node(tx, ty, tn.dir, (tn.color+1)%5, tn.step+1));
            }
        }
        // right rotate
        tx = tn.x, ty = tn.y;
        if(dp[tx][ty][(tn.dir+1)%4][tn.color] == 0) {
            dp[tx][ty][(tn.dir+1)%4][tn.color] = tn.step+1;
            Q.push(Node(tx, ty, (tn.dir+1)%4, tn.color, tn.step+1));
        }
        // left rotate
        if(dp[tx][ty][(tn.dir+3)%4][tn.color] == 0) {
            dp[tx][ty][(tn.dir+3)%4][tn.color] = tn.step+1;
            Q.push(Node(tx, ty, (tn.dir+3)%4, tn.color, tn.step+1));
        }
    }
    if(ret < 0)
        puts("destination not reachable");
    else
        printf("minimum time = %d sec\n", ret);
}
int main() {
    int cases = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        if(cases)   puts("");
        printf("Case #%d\n", ++cases);
        int i, j;
        for(i = 0; i < n; i++) {
            scanf("%s", g[i]);
            for(j = 0; j < m; j++) {
                if(g[i][j] == 'S')
                    sx = i, sy = j;
                if(g[i][j] == 'T')
                    ex = i, ey = j;
            }
        }
        sol();
    }
    return 0;
}
