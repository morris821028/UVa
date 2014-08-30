#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
// euler path

#define MAXN 10005
int dist[MAXN], visited[MAXN];
vector<int> g[MAXN];
void dfs(int u) {
	visited[u] = 1;
	for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (visited[v]) continue;
		dist[v] = dist[u]+1;
		dfs(v);
	}
}
int tree_diameter(int n) {
    memset(visited, 0, sizeof(visited));
    dist[1] = 0, dfs(1);
    
    int p = (int)(max_element(dist + 1, dist + n + 1) - dist);
    memset(visited, 0, sizeof(visited));
    dist[p] = 0, dfs(p);
    return *(max_element(dist + 1, dist + n + 1));
}
int main() {
    int testcase, n, m, x;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &m);
            g[i].clear();
            for (int j = 0; j < m; j++) {
                scanf("%d", &x);
                g[i].push_back(x);
            }
        }
        printf("%d\n", (2 * n - 2) - tree_diameter(n));
    }
    return 0;
}

/*
 2
 2
 1 2
 1 1
 5
 3 2 3 4
 1 1
 2 1 5
 1 1
 1 3
 */
