#include <stdio.h>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
struct Pt {
    int x, y;
};
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        cin.ignore(100, '\n');
        string line;
        int g[101][101] = {}, x, y;
        for(i = 1; i < n; i++) {
            getline(cin, line);
            stringstream sin(line);
            while(sin >> x >> y)
                g[x][y] = i;
        }
        int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
        int usedNum[101] = {}, used[101][101] = {};
        int err = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n && !err; j++) {
                if(used[i][j] == 0) {
                    if(usedNum[g[i][j]]) {
                        err = 1;
                        break;
                    }
                    usedNum[g[i][j]] = 1;
                    queue<Pt> Q;
                    Pt tn, tmp;
                    tn.x = i, tn.y = j;
                    used[i][j] = 1;
                    Q.push(tn);
                    while(!Q.empty()) {
                        tn = Q.front();
                        Q.pop();
                        for(k = 0; k < 4; k++) {
                            x = tn.x+dir[k][0], y = tn.y+dir[k][1];
                            if(x <= 0 || y <= 0 || x > n || y > n)
                                continue;
                            if(g[x][y] != g[tn.x][tn.y])
                                continue;
                            if(used[x][y] == 0) {
                                used[x][y] = 1;
                                tmp.x = x, tmp.y = y;
                                Q.push(tmp);
                            }
                        }
                    }
                }
            }
        }
        if(err == 1)
            puts("wrong");
        else
            puts("good");
    }
    return 0;
}
