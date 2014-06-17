#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
char g[105][105];
int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
int n, m, i, j, p;
int check(int x, int y, int c) {
    int tx, ty, i;
    for(i = 0; i < 4; i++) {
        tx = x+dir[i][0], ty = y+dir[i][1];
        if(tx < 0 || ty < 0 || tx >= n || ty >= m)
            continue;
        if(g[tx][ty] != '.' && g[tx][ty] != c)
            return 0;
    }
    return 1;
}
int main() {
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        memset(g, 0, sizeof(g));
        for(i = 0; i < n; i++)
            scanf("%s", g[i]);
        int alph[26] = {}, x, y, tx, ty;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] >= 'A' && g[i][j] <= 'Z'
                   && g[i][j] == g[i][j+1] && g[i][j] == g[i+1][j]) { // left upper corner
                    if(g[i+1][j+1] == '.') {
                        queue<int> X, Y;
                        X.push(i+1), Y.push(j+1);
                        int flag = 1; // true
                        char used[105][105] = {};
                        while(!X.empty() && flag) {
                            x = X.front(), X.pop();
                            y = Y.front(), Y.pop();
                            flag &= check(x, y, g[i][j]);
                            for(p = 0; p < 4; p++) {
                                tx = x+dir[p][0], ty = y+dir[p][1];
                                if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                                    continue;
                                if(used[tx][ty] || g[tx][ty] != '.')
                                    continue;
                                used[tx][ty] = 1;
                                X.push(tx), Y.push(ty);
                            }
                        }
                        if(flag)    alph[g[i][j]-'A'] = 1;
                    }
                }
            }
        }
        for(i = 0; i < 26; i++)
            if(alph[i])
                putchar(i+'A');
        puts("");
    }
    return 0;
}
