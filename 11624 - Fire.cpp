#include <stdio.h>
#include <queue>
using namespace std;
char g[1010][1010];
int F[1010][1010], J[1010][1010];
int n, m, dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
struct pt {
    int x, y;
};
pt pf, pj;
queue<pt> Q;
void sol() {
    int i, j;
    while(!Q.empty())   Q.pop();
    pt tn, tx;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            if(g[i][j] == 'F') {
                pf.x = i, pf.y = j;
                Q.push(pf);
                F[pf.x][pf.y] = 1;
            }
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(i = 0; i < 4; i++) {
            tx.x = tn.x+dir[i][0];
            tx.y = tn.y+dir[i][1];
            if(tx.x < 0 || tx.x >= n || tx.y < 0 || tx.y >= m)
                continue;
            if(g[tx.x][tx.y] == '#')
                continue;
            if(F[tx.x][tx.y] == 0) {
                F[tx.x][tx.y] = F[tn.x][tn.y]+1;
                Q.push(tx);
            }
        }
    }
    Q.push(pj), J[pj.x][pj.y] = 1;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        if(tn.x == 0 || tn.y == 0 || tn.x == n-1 || tn.y == m-1) {
            printf("%d\n", J[tn.x][tn.y]);
            return;
        }
        for(i = 0; i < 4; i++) {
            tx.x = tn.x+dir[i][0];
            tx.y = tn.y+dir[i][1];
            if(tx.x < 0 || tx.x >= n || tx.y < 0 || tx.y >= m)
                continue;
            if(g[tx.x][tx.y] == '#')
                continue;
            if(J[tx.x][tx.y] == 0 && (J[tn.x][tn.y]+1 < F[tx.x][tx.y] || F[tx.x][tx.y] == 0)) {
                J[tx.x][tx.y] = J[tn.x][tn.y]+1;
                Q.push(tx);
            }
        }
    }
    puts("IMPOSSIBLE");
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            scanf("%s", g[i]);
            for(j = 0; j < m; j++) {
                if(g[i][j] == 'J')
                    pj.x = i, pj.y = j;
                F[i][j] = 0, J[i][j] = 0;
            }
        }
        sol();
    }
    return 0;
}
