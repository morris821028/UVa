#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define MAXN 131072
vector< pair<int, int> > g[MAXN];
int dist[MAXN][3], visited[MAXN], preColor[MAXN], ret[MAXN];
void bfs(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i][0] = dist[i][1] = dist[i][2] = 0;
        visited[i] = 0, ret[i] = 0x3f3f3f3f, preColor[i] = 0x3f3f3f3f;
    }
    queue<int> Q;
    Q.push(n), dist[n][0] = 1;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first, c = g[u][i].second;
            if (dist[v][0] == 0) {
                dist[v][0] = dist[u][0] + 1;
                dist[v][1] = u, dist[v][2] = c;
                Q.push(v);
            }
            if (dist[v][0] == dist[u][0] + 1 && c < dist[v][2]) {
                dist[v][1] = u, dist[v][2] = c;
            }
        }
    }
    Q.push(1), visited[1] = 1;
    ret[dist[1][0]] = dist[1][2];
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (u != 1 && preColor[u] != ret[dist[u][0]])
            continue;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first, c = g[u][i].second;
            if (dist[v][0] == dist[u][0] - 1) {
                preColor[v] = min(preColor[v], c);
                ret[dist[v][0]] = min(ret[dist[v][0]], c);
                if (visited[v] == 0) {
                    visited[v] = 1;
                    Q.push(v);
                }
            }
        }
    }
    printf("%d\n", dist[1][0] - 1);
    for (int i = dist[1][0] - 1; i >= 1; i--) {
        printf("%d%c", ret[i], i == 1 ? '\n' : ' ');
    }
}
int main() {
    int n, m, x, y, c;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++)
            g[i].clear();
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &c);
            g[x].push_back(make_pair(y, c));
            g[y].push_back(make_pair(x, c));
        }
        bfs(n);
    }
    return 0;
}
/*
 4 6
 1 2 1
 1 3 2
 3 4 3
 2 3 1
 2 4 4
 3 1 1
 
 4 4
 1 2 1
 1 3 1
 2 4 4
 3 4 3
 
 20 26
 7 16 1
 16 12 1
 17 9 6
 2 16 1
 14 16 1
 1 11 1
 18 16 1
 1 14 1
 1 15 1
 1 18 1
 5 3 4
 1 10 1
 9 6 2
 15 16 1
 4 16 1
 8 20 2
 19 8 8
 10 16 1
 6 19 3
 12 5 7
 1 4 1
 13 17 6
 1 2 1
 1 7 1
 11 16 1
 3 13 8

 */