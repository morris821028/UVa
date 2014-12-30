#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
#define MAXN 128
vector<int> g[MAXN][MAXN];

struct Survey {
    int x, y, h;
    Survey(int a = 0, int b = 0, int c = 0):
    x(a), y(b), h(c) {}
};
vector< vector<Survey> > D;
int n, m;

int spfa(int sx, int sy) {
    int ret[MAXN][MAXN], used[MAXN][MAXN] = {};
    vector<int> sid;
    sid.resize(D.size(), 0);
    int x, y, h, id, tx, ty;
    queue<int> X, Y, ID;
    used[sx][sy] = 1, ret[sx][sy] = 0;
    for (int i = 0; i < g[sx][sy].size(); i++) {
        int u = g[sx][sy][i];
        X.push(sx), Y.push(sy), ID.push(u);
        sid[u] = 1;
    }
    while (!X.empty()) {
        x = X.front(), X.pop();
        y = Y.front(), Y.pop();
        id = ID.front(), ID.pop();
        int shift = 0;
        for (int i = 0; i < D[id].size(); i++) {
            if (D[id][i].x == x && D[id][i].y == y) {
                shift = ret[x][y] - D[id][i].h;
                break;
            }
        }
        for (int i = 0; i < D[id].size(); i++) {
            tx = D[id][i].x, ty = D[id][i].y;
            h = D[id][i].h + shift;
            if (used[tx][ty] && h != ret[tx][ty])
                return 0;
            ret[tx][ty] = h;
            if (used[tx][ty] == 0) {
                used[tx][ty] = 1;
                for (int j = 0; j < g[tx][ty].size(); j++) {
                    int u = g[tx][ty][j];
                    if (sid[u]) continue;
                    X.push(tx), Y.push(ty), ID.push(u);
                    sid[u] = 1;
                }
            }
        }
    }
    
    int ok = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ok &= used[i][j];
        }
    }
    if (ok) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                printf("%d%c", ret[i][j], j == m ? '\n' : ' ');
            }
        }
    } else {
        puts("the lack of measurements");
    }
    return 1;
}
char line[1048576 * 8];
int main() {
    int testcase, bx, by;
    int x, y, h;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        scanf("%d %d", &bx, &by);
        while (getchar() != '\n');
        
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                g[i][j].clear();
        D.clear();
        while (gets(line)) {
            if (line[0] == '\0')   break;
            stringstream sin(line);
            int id = (int) D.size();
            vector<Survey> item;
            while (sin >> x >> y >> h) {
                item.push_back(Survey(x, y, h));
                g[x][y].push_back(id);
            }
            D.push_back(item);
        }
        int f = spfa(bx, by);
        if (!f) {
            puts("conflicting measurements");
        }
        if (testcase)
            puts("");
    }
    return 0;
}
/*
 3
 
 2 2
 1 2
 1 1 10 1 2 10
 1 1 20 2 2 30 2 1 30
 
 2 2
 1 1
 1 1 10 1 2 10
 
 2 2
 1 2
 1 1 10 1 2 10
 1 1 20 1 2 30
 */
