#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

struct Edge {
    int to, w, i;
    Edge(int a = 0, int b = 0, int c = 0):
        to(a), w(b), i(c) {}
};
vector<Edge> g[16];
int n, used[1<<16];
double dp[1<<16];
double dfs(int);

void dfs2(int u, int mask, int w, int e, int o) {
    if (e) {
        dp[o] = min(dp[o], dfs(mask) + (double)w/e);
    }
    for (int i = 0; i < g[u].size(); i++) {
        if ((mask>>g[u][i].i)&1) {
            int v = g[u][i].to;
            dfs2(v, mask^(1<<g[u][i].i), w + g[u][i].w, e+1, o);
        }
    }
}
double dfs(int mask) {
    if (mask == 0)  return 0;
    if (used[mask]) return dp[mask];
    used[mask] = 1;
    double &ret = dp[mask];
    ret = 1e+30;
    for (int i = 0; i < n; i++) {
        dfs2(i, mask, 0, 0, mask);
    }
    return ret;
}
int main() {
    int x, y, w;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            g[i].clear();
        for (int i = 0; i < n - 1; i++) {
            scanf("%d %d %d", &x, &y, &w);
            g[x].push_back(Edge(y, w, i));
            g[y].push_back(Edge(x, w, i));
        }
        memset(used, 0, sizeof(used));
        printf("%.4lf\n", dfs((1<<(n-1)) - 1));
    }
    return 0;
}

/*
 4
 0 2 1
 1 2 2
 2 3 3
 6
 0 1 10000
 0 2 10000
 0 3 1
 0 4 1
 0 5 10000
 0 */