#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include <assert.h>
using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const char sdir[] = "NESW";
const int banDir[] = {3, 0, 1, 2}, invDir[] = {2, 3, 0, 1};
#define MAXN 1000
char g[MAXN + 5][MAXN + 5];
int dist[MAXN + 5][MAXN + 5][4], used[MAXN + 5][MAXN + 5][4], cases = 0; // [x][y][from_direction]
int followRegion[5][2] = {{}, {2, 3}, {0, 3}, {1, 2}, {0, 1}};
int isValidPos(int x, int y) {
    return x >= 0 && y >= 0 && x <= MAXN && y <= MAXN && g[x][y] == ' ';
}
void bfs(int sx, int sy, int sd, int ex, int ey, int eregion) {
    sx += dx[sd], sy += dy[sd];
//    printf("%d %d %d -> %d %d %d\n", sx, sy, sd, ex, ey, eregion);
    if (!isValidPos(sx, sy)) {
        puts("QQ");
        return ;
    }
    cases++;
    used[sx][sy][sd] = cases, dist[sx][sy][sd] = 1;
    int tx, ty, td;
    queue<int> X, Y, D;
    X.push(sx), Y.push(sy), D.push(sd);
    while (!X.empty()) {
        sx = X.front(), X.pop();
        sy = Y.front(), Y.pop();
        sd = D.front(), D.pop();
//        printf("%d %d %d - %d\n", sx, sy, sd, dist[sx][sy][sd]);
        for (int i = 0; i < 4; i++) {
            if (i == banDir[sd] || i == invDir[sd])    continue;
            tx = sx + dx[i], ty = sy + dy[i], td = i;
            if (isValidPos(tx, ty)) {
                if (used[tx][ty][td] != cases) {
                    dist[tx][ty][td] = dist[sx][sy][sd] + 1;
                    used[tx][ty][td] = cases;
                    X.push(tx), Y.push(ty), D.push(td);
                }
            }
        }
        if (used[ex][ey][followRegion[eregion][0]] == cases ||
            used[ex][ey][followRegion[eregion][1]] == cases) {
            int x = 0x3f3f3f3f, y = 0x3f3f3f3f;
            if (used[ex][ey][followRegion[eregion][0]] == cases)
                x = dist[ex][ey][followRegion[eregion][0]];
            if (used[ex][ey][followRegion[eregion][1]] == cases)
                y = dist[ex][ey][followRegion[eregion][1]];
            printf("%d\n", min(x, y));
            return;
        }
    }
    puts("QQ");
}
int main() {
    int testcase;
    int sx, sy, ex, ey, eregion, m, x, y;
    char s[128];
    scanf("%d", &testcase);
    while (testcase--) {
        memset(g, ' ', sizeof(g));
        scanf("%d %d %s", &sx, &sy, s);
        scanf("%d %d %d", &ex, &ey, &eregion);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            g[x][y] = '#';
        }
        int sd = (int) (find(sdir, sdir + 4, s[0]) - sdir);
        bfs(sx, sy, sd, ex, ey, eregion);
    }
    return 0;
}
/*
 7
 1 2 E
 4 2 1
 0
 1 2 E
 4 2 2
 0
 1 2 E
 4 2 3
 0
 1 2 E
 4 2 4
 0
 1 2 E
 4 2 3
 1
 3 2
 1 2 E
 4 2 3
 1
 2 2
 1 2 E
 4 2 3
 4
 3 2 
 5 2
 4 1
 4 3
 */