#include <stdio.h>
#include <string.h>
#include <queue>
#define N 105
#define oo 0xfffffff
using namespace std;
struct node {
    int cap, cost;
} g[N][N];
int dist[N], pre[N], used[N];
int spfa(int src, int sink) {
    queue<int> Q;
    int i, j, tn;
    for(i = 0; i <= sink; i++)
        dist[i] = oo, used[i] = 0;
    dist[src] = 0, used[src] = 1;
    Q.push(src);
    pre[src] = src;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(i = 0; i <= sink; i++) {
            if(g[tn][i].cap > 0 && dist[i] > dist[tn]+g[tn][i].cost) {
                dist[i] = dist[tn]+g[tn][i].cost;
                pre[i] = tn;
                if(!used[i])
                    Q.push(i), used[i] = 1;
            }
        }
    }
    return dist[sink] != oo;
}
int mincost(int src, int sink) {
    int ans = 0, flow, i;
    while(spfa(src, sink)) {
        flow = oo;
        for(i = sink; i != src; i = pre[i])
            if(flow > g[pre[i]][i].cap)
                flow = g[pre[i]][i].cap;
        for(i = sink; i != src; i = pre[i]) {
            g[pre[i]][i].cap -= flow;
            g[i][pre[i]].cap += flow;
            g[i][pre[i]].cost = -g[pre[i]][i].cost;
        }
        ans += dist[sink]*flow;
    }
    return ans;
}
int main() {
    int n, m, x, y, v;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        memset(g, 0, sizeof(g));
        while(m--) {
            scanf("%d %d %d", &x, &y, &v);
            g[x][y].cap = g[y][x].cap = 1;
            g[x][y].cost = g[y][x].cost = v;
        }
        g[0][1].cap = g[1][0].cap = 2;
        g[n][n+1].cap = g[n+1][n].cap = 2;
        int ans = mincost(0, n+1);
        if(g[1][0].cap != 4)
            puts("Back to jail");
        else
            printf("%d\n", ans);
    }
    return 0;
}
