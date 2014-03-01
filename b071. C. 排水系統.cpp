#include <stdio.h>
#include <queue>
using namespace std;
int g[500][500], used[500][500];
struct Pt {
    int x, y;
};
int main() {
    int t, n, m, i, j, k, tx, ty;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &g[i][j]);
                used[i][j] = 0;
            }
        }
        queue<Pt> Q;
        Pt p, tmp;
        int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                for(k = 0; k < 4; k++) {
                    tx = i+dir[k][0], ty = j+dir[k][1];
                    if(tx < 0 || ty < 0 || tx >= n || ty >= n)
                        continue;
                    if(g[tx][ty] < g[i][j]) break;
                }
                if(k == 4) {
                    p.x = i, p.y = j;
                    Q.push(p);
                    used[i][j] = 1;
                }
            }
        }
        if(Q.size() > m) {
            puts("Impossible");
            continue;
        }
        while(!Q.empty()) {
            p = Q.front();
            Q.pop();
            for(i = 0; i < 4; i++) {
                tx = p.x+dir[i][0], ty = p.y+dir[i][1];
                if(tx < 0 || ty < 0 || tx >= n || ty >= n)
                    continue;
                if(g[tx][ty] < g[p.x][p.y])
                    continue;
                if(!used[tx][ty]) {
                    used[tx][ty] = used[p.x][p.y]+1;
                    tmp.x = tx, tmp.y = ty;
                    Q.push(tmp);
                }
            }
        }
        printf("%d\n", used[p.x][p.y]-1);
    }
    return 0;
}
