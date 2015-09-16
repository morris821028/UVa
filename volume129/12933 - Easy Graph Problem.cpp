#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
const int MAXN = 512;
const int INF = 0x3f3f3f3f;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int g[MAXN][MAXN], dist[MAXN][MAXN], dist2[MAXN][MAXN][4];
int n, m, sx, sy, ex, ey;
void dijkstra(int sx, int sy) {
    typedef pair<long long, pair<int, int> > PLL;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            dist[i][j] = INF;
    }
    
    set<PLL> pQ;
    PLL u;
    pQ.insert(PLL(g[sx][sy], {sx, sy})), dist[sx][sy] = g[sx][sy];
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        int x, y, tx, ty;
        x = u.second.first, y = u.second.second;
        for (int i = 0; i < 4; i++) {
            tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > m)
                continue;
            if (g[tx][ty] == 0)
                continue;
            if (dist[tx][ty] > dist[x][y] + g[tx][ty]) {
                if (dist[tx][ty] != INF)
                    pQ.erase(pQ.find(PLL(dist[tx][ty], {tx, ty})));
                dist[tx][ty] = dist[x][y] + g[tx][ty];
                pQ.insert(PLL(dist[tx][ty], {tx, ty}));
            }
        }
    }
}
void dijkstra_turn(int sx, int sy) {
    struct E {
        int x, y, d;
        bool operator<(const E &a) const {
            if (x != a.x)   return x < a.x;
            if (y != a.y)   return y < a.y;
            return d < a.d;
        }
    };
    typedef pair<long long, E> PLL;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < 4; k++)
                dist2[i][j][k] = INF;
    }
    
    set<PLL> pQ;
    PLL u;
    int x, y, tx, ty, d;
    for (int i = 0; i < 4; i++) {
        x = sx, y = sy;
        tx = x + dx[i], ty = y + dy[i];
        if (tx < 1 || ty < 1 || tx > n || ty > m)
            continue;
        if (g[tx][ty] == 0)
            continue;
        dist2[tx][ty][i] = g[sx][sy] + g[tx][ty];
        pQ.insert(PLL(g[tx][ty], {tx, ty, i}));
    }
    while (!pQ.empty()) {
        u = *pQ.begin(), pQ.erase(pQ.begin());
        x = u.second.x, y = u.second.y, d = u.second.d;
        for (int i = 0; i < 4; i++) {
            tx = x + dx[i], ty = y + dy[i];
            if (i == d) continue;
            if (tx < 1 || ty < 1 || tx > n || ty > m)
                continue;
            if (g[tx][ty] == 0)
                continue;
            if (dist2[tx][ty][i] > dist2[x][y][d] + g[tx][ty]) {
                if (dist2[tx][ty][i] != INF)
                    pQ.erase(pQ.find(PLL(dist2[tx][ty][i], {tx, ty, i})));
                dist2[tx][ty][i] = dist2[x][y][d] + g[tx][ty];
                pQ.insert(PLL(dist2[tx][ty][i], {tx, ty, i}));
            }
        }
    }
}
int main() {
    int cases = 0;
    char s[128];
    while (scanf("%d %d", &n, &m) == 2) {
        scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%s", s);
                if (s[0] == '*')
                    g[i][j] = 0;
                else
                    sscanf(s, "%d", &g[i][j]);
            }
        }
        printf("Case %d: ", ++cases);
        dijkstra(sx, sy);
        if (dist[ex][ey] == INF)
            printf("-1 ");
        else
            printf("%d ", dist[ex][ey]);
        dijkstra_turn(sx, sy);
        int ret = INF;
        for (int i = 0; i < 4; i++)
            ret = min(ret, dist2[ex][ey][i]);
        if (ret == INF)
            printf("-1");
        else
            printf("%d", ret);
        puts("");
    }
    return 0;
}