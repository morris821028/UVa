#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int n, m, max_coin;
char g[16][16];

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

void dfs(int sx, int sy, int mask, int coins) {
    queue<int> X, Y;
    vector< pair<int, int> > cc;
    int tx, ty;
    int used[16][16] = {};
    // eat coins
    X.push(sx), Y.push(sy);
    while (!X.empty()) {
        sx = X.front(), X.pop();
        sy = Y.front(), Y.pop();
        for (int i = 0; i < 4; i++) {
            tx = sx + dx[i], ty = sy + dy[i];
            if (tx < 0 || ty < 0 || tx >= n || ty >= m || (g[tx][ty] != '.' && g[tx][ty] != 'C'))
                continue;
            if (!used[tx][ty]) {
                used[tx][ty] = 1;
                if (g[tx][ty] == 'C') {
                    g[tx][ty] = '.';
                    cc.push_back(make_pair(tx, ty));
                    coins++;
                }
                X.push(tx), Y.push(ty);
            }
        }
    }
    max_coin = max(max_coin, coins);
    for (int i = 0; i < n; i++) { // push stone
        for (int j = 0; j < m; j++) {
            if (!(g[i][j] >= '0' && g[i][j] <= '9'))
                continue;
            int x = g[i][j] - '0';
            if ((mask>>x)&1) {
                for (int k = 0; k < 4; k++) {
                    tx = i + dx[k], ty = j + dy[k];
                    if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                        continue;
                    if (used[tx][ty]) { // can arrive
                        tx = i + dx[(k+2)%4], ty = j + dy[(k+2)%4];
                        if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                            continue;
                        if (g[tx][ty] == '.') {
                            swap(g[i][j], g[tx][ty]);
//                            for (int p = 0; p < n; p++) {
//                                printf("%s\n", g[p]);
//                            }
//                            puts("--");
                            dfs(i, j, mask^(1<<x), coins);
                            swap(g[i][j], g[tx][ty]);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < cc.size(); i++) {
        g[cc[i].first][cc[i].second] = 'C';
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        int sx, sy, stone = 0;
        sx = sy = -1;
        for (int i = 0; i < n; i++) {
            scanf("%s", g[i]);
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'S') {
                    sx = i, sy = j;
                    g[i][j] = '.';
                } else if (g[i][j] == 'O') {
                    g[i][j] = stone + '0';
                    stone++;
                }
            }
        }
        
        assert(sx >= 0 && sy >= 0);
        max_coin = 0;
        dfs(sx, sy, (1<<stone)-1, 0);
        printf("%d\n", max_coin);
    }
    return 0;
}

/*
 3
 3 4
 S.OC
 ..O.
 .XCX
 4 6
 S.X.CC
 ..XOCC
 ...O.C
 ....XC
 4 4
 .SXC
 OO.C
 ..XX
 .CCC
 */