#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;

#define MAXN 262144
struct edge {
    int to, v;
    edge(int a = 0, int b = 0):
    to(a), v(b) {}
};
vector<edge> g[MAXN];
int dp[MAXN];
int used[MAXN];
void dfs(int u, int p) {
    used[u] = 1;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to, w = g[u][i].v;
        if(used[v])    continue;
        dfs(v, u);
    }
    
    int ret = 0;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to, w = g[u][i].v;
        if(v == p)    continue;
        if (dp[v] + w > 0) {
            ret += dp[v] + w;
        }
    }
    dp[u] = ret;
}
map<int, int> R;

int rename(int x) {
    int &ret = R[x];
    return ret == 0 ? ret = (int)R.size() : ret;
}
int main() {
    int n, x, y, v;
    while(scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= R.size(); i++)
            g[i].clear();
        R.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &x, &y, &v);
            x = rename(x), y = rename(y);
            g[x].push_back(edge(y, v));
            g[y].push_back(edge(x, v));
//            printf("-- %d %d %d\n", x, y, v);
        }
        
        n = (int)R.size();
        for (int i = 1; i <= n; i++)
            dp[i] = 0;
        for (int i = 1; i <= n; i++)
            used[i] = 0;
        for (int i = 1; i <= n; i++) {
            if (used[i] == 0) {
                dfs(i, -1);
            }
        }
        
        int ret = 0;
        for (int i = 1; i <= n; i++) {
            ret = max(ret, dp[i]);
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 4
 1 2 -7
 3 2 10
 2 4 2
 5 4 -2
 3
 1 2 -8
 2 3 -8
 3 4 -1000
 5
 14 15 0
 15 92 10
 92 65 -5
 65 35 10
 35 89 -30
 0
*/