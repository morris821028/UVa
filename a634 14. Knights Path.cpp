#include <stdio.h>
#include <string.h>
#include <iostream>
#include <set>
#include <queue>
using namespace std;
int g[8][8];
int dir[8][2] = {{1,2},{1,-2},{-1,2},{-1,-2},
{2,1},{2,-1},{-2,1},{-2,-1}};
set<string> sol;
int used[8][8], x, y, i, j;
char bufres[1024];
void dfs(int sx, int sy) {
    if(used[sx][sy] == 1) {
        sol.insert(bufres);
        return;
    }
    int i, x, y, l = (used[sx][sy]-1)*3;
    for(i = 0; i < 8; i++) {
        x = sx+dir[i][0], y = sy+dir[i][1];
        if(x < 0 || y < 0 || x >= 8 || y >= 8)
            continue;
        if(g[x][y])
            continue;
        if(used[x][y] == used[sx][sy]-1) {
            bufres[l-1] = y+'1';
            bufres[l-2] = x+'a';
            bufres[l-3] = ' ';
            dfs(x, y);
        }
    }
}
void bfs(int sx, int sy, int ex, int ey) {
    queue<int> X, Y;
    X.push(sx), Y.push(sy);
    memset(used, 0, sizeof(used));
    used[sx][sy] = 1;
    while(!X.empty()) {
        sx = X.front(), X.pop();
        sy = Y.front(), Y.pop();
        for(i = 0; i < 8; i++) {
            x = sx+dir[i][0], y = sy+dir[i][1];
            if(x < 0 || y < 0 || x >= 8 || y >= 8)
                continue;
            if(g[x][y] || used[x][y])
                continue;
            used[x][y] = used[sx][sy]+1;
            X.push(x), Y.push(y);
        }
    }
    printf("The shortest solution is %d move(s).\n", used[ex][ey]-1);
    memset(bufres, 0, sizeof(bufres));
    int l = used[ex][ey]*3;
    bufres[l-1] = ey+'1';
    bufres[l-2] = ex+'a';
    bufres[l-3] = ' ';
    dfs(ex, ey);
    set<string>::iterator it = sol.end();;
    it--;
    cout << "Solution:" << *it << endl;
    /*for(set<string>::iterator it = sol.begin();
        it != sol.end(); it++) {
        cout << "Solution:" << *it << endl;
    }*/
    sol.clear();
}
int main() {
    char s[5];
    int sx, sy, ex, ey, x, y;
    while(scanf("%s", s) == 1) {
        sx = s[0]-'a', sy = s[1]-'1';
        scanf("%s", s);
        ex = s[0]-'a', ey = s[1]-'1';
        memset(g, 0, sizeof(g));
        while(scanf("%s", s) == 1 && s[0] != 'x') {
            x = s[0]-'a', y = s[1]-'1';
            g[x][y] = -1;
        }
        bfs(sx, sy, ex, ey);
    }
    return 0;
}
