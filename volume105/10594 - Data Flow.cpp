#include <stdio.h>
#include <string.h>
#include <queue>
#define N 105
#define oo 2147483647
using namespace std;
struct node {
    int cap, cost;
} g[N][N];
long long dist[N];
int pre[N], used[N], D, K;
long long spfa(int src, int sink) {
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
long long mincost(int src, int sink) {
    long long ans = 0, flow, totflow = 0;
    int i;
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
        totflow += flow;
    }
    if(totflow != D)
        return -1;
    return ans;
}
int main() {
    int n, m, i, x[5010], y[5010], v[5010];
    while(scanf("%d %d", &n, &m) == 2) {
        memset(g, 0, sizeof(g));
        for(i = 0; i < m; i++)
            scanf("%d %d %d", &x[i], &y[i], &v[i]);
        scanf("%d %d", &D, &K);
        for(i = 0; i < m; i++) {
            g[x[i]][y[i]].cap = K;
            g[x[i]][y[i]].cost = v[i];
            g[y[i]][x[i]].cap = K;
            g[y[i]][x[i]].cost = v[i];
        }
        g[0][1].cap = D;
        g[0][1].cost = 0;
        g[n][n+1].cap = D;
        g[n][n+1].cost = 0;
        long long res = mincost(0, n+1);
        if (res >= 0)
            printf("%lld\n", res);
        else
            printf("Impossible.\n");
    }
    return 0;
}
