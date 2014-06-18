#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
char g[1005][1005];
short used[1005][1005];
short dist[1005][1005];
int n, m;
struct E {
    short x, y, d, h;
    E(short a, short b, short c, short dd):
        x(a), y(b), d(c), h(dd){}
    bool operator<(const E &a) const {
        if(d != a.d)
            return d > a.d;
        return h > a.h;
    }
};
priority_queue<E, vector<E> > pQ;
void sol(int sx, int sy, int ex, int ey) {
    static int times = 0;
    times++;
    while(!pQ.empty())  pQ.pop();
    E tn(0,0,0,0);
    pQ.push(E(sx, sy, 0, ex-sx+ey-sy));
    int dx[] = {-1,-1,0,1,1,1,0,-1};
    int dy[] = {0,1,1,1,0,-1,-1,-1};
    int i, cost, tx, ty, dir;
    used[sx][sy] = times;
    dist[sx][sy] = 0;
    while(!pQ.empty()) {
        tn = pQ.top(), pQ.pop();
        if(tn.x == ex && tn.y == ey) {
            printf("%d\n", tn.d);
            break;
        }
        dir = g[tn.x][tn.y] -'0';
        short &o = dist[tn.x][tn.y];
        for(i = 0; i < 8; i++) {
            tx = tn.x + dx[i], ty = tn.y + dy[i];
            if(tx < 0 || tx >= n || ty < 0 || ty >= m)
                continue;
            cost = 0;
            if(dir != i)
                cost = 1;
            if(dist[tx][ty] > o+cost || used[tx][ty] != times) {
                used[tx][ty] = times;
                dist[tx][ty] = o+cost;
                pQ.push(E(tx, ty, dist[tx][ty], ex-tx+ey-ty));
            }
        }
    }
}
int main() {
    int i, q, sx, sy, ex, ey;
    while(scanf("%d %d", &n, &m) == 2) {
        while(getchar() != '\n');
        for(i = 0; i < n; i++)
            gets(g[i]);
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
            sx--, sy--, ex--, ey--;
            sol(sx, sy, ex, ey);
        }
    }
    return 0;
}
