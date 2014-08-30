#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
// http://en.wikipedia.org/wiki/Topological_sort

vector<int> g[1024], topo;
int visited[1024];

void dfs(int u) {
    visited[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (visited[v]) continue;
        dfs(v);
    }
    topo.push_back(u);
}
void dfs2(int u) {
    visited[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (visited[v]) continue;
        dfs(v);
    }
}

int main() {
    int n, m, x, y;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i <= n; i++)
            g[i].clear();
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            if (y == 0)
                continue;
            g[x].push_back(y);
        }
        memset(visited, 0, sizeof(visited));
        topo.clear();
        for (int i = 0; i <= n; i++) {
            if (visited[i] == 0)
                dfs(i);
        }
        reverse(topo.begin(), topo.end());
        memset(visited, 0, sizeof(visited));
        
        int ret = 0;
        for (int i = 0; i < topo.size(); i++) {
            int u = topo[i];
            if (visited[u]) continue;
            ret++;
            dfs2(u);
        }
        printf("%d\n", ret - 1);
    }
    return 0;
}
/*
 4 5
 0 1
 1 2
 2 1
 0 4
 3 4
 4 2
 3 1
 2 1
 */