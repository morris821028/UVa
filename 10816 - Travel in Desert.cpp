#include <stdio.h>
#include <vector>
#define oo 0xffffff
#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))
using namespace std;
typedef struct {
    int x, r, d;
} arc;
vector<arc> g[105];
int cutR, dist[105], used[105], pre[105];
int n, m, st, ed, x, y;
int a, b, c, d, i, j;
void dijsktra1() {
    for(i = 1; i <= n; i++)
        dist[i] = oo, used[i] = 0;
    dist[st] = 0;
    for(i = 1; i <= n; i++) {
        int mn = oo, idx;
        for(j = 1; j <= n; j++)
            if(used[j] == 0 && dist[j] < mn)
                mn = dist[j], idx = j;
        if(idx == ed) {
            cutR = dist[ed];
            return;
        }
        used[idx] = 1;
        for(vector<arc>::iterator it = g[idx].begin();
            it != g[idx].end(); it++) {
            dist[it->x] = min(dist[it->x], max(dist[idx], it->r));
        }
    }
}
void dijsktra2() {
    for(i = 1; i <= n; i++)
        dist[i] = oo, used[i] = 0;
    dist[ed] = 0;
    for(i = 1; i <= n; i++) {
        int mn = oo, idx;
        for(j = 1; j <= n; j++)
            if(used[j] == 0 && dist[j] < mn)
                mn = dist[j], idx = j;
        if(idx == st) {
            for(i = st; dist[i]; i = pre[i])
                printf("%d ", i);
            printf("%d\n", ed);
            printf("%.1lf %.1lf\n", dist[st]/10.0, cutR/10.0);
            return;
        }
        used[idx] = 1;
        for(vector<arc>::iterator it = g[idx].begin();
            it != g[idx].end(); it++) {
            if(it->r <= cutR) {
                if(dist[it->x] > dist[idx]+it->d) {
                    dist[it->x] = dist[idx]+it->d;
                    pre[it->x] = idx;
                }
            }
        }
    }
}
int main() {
    while(scanf("%d %d", &n, &m) == 2) {
        scanf("%d %d", &st, &ed);
        for(i = 1; i <= n; i++)
            g[i].clear();
        arc e;
        while(m--) {
            scanf("%d %d %d.%d %d.%d", &x, &y, &a, &b, &c, &d);
            a = a*10+b, c = c*10+d;
            e.x = y, e.r = a, e.d = c;
            g[x].push_back(e);
            e.x = x;
            g[y].push_back(e);
        }
        dijsktra1();
        dijsktra2();
    }
    return 0;
}
