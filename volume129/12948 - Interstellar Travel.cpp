#include <stdio.h>
#include <limits.h>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
struct Edge {
    int to, cc, tt;
    Edge(int a = 0, int b = 0, int c = 0):
    to(a), cc(b), tt(c) {}
};
const int MAXN = 305;
vector<Edge> g[MAXN];
pair<int, int> dist[MAXN][MAXN];
int inq[MAXN][MAXN];
void spfa(int st, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 301; j++)
            dist[i][j] = make_pair(INT_MAX, INT_MAX), inq[i][j] = 0;
    }
    dist[st][0] = make_pair(0, 0);
    queue<int> Q, P;
    Q.push(st), P.push(0);
    while (!Q.empty()) {
        int u, v, p;
        u = Q.front(), Q.pop();
        p = P.front(), P.pop();
        for (auto &e : g[u]) {
            pair<int, int> c;
            c.first = dist[u][p].first + e.cc;
            c.second = dist[u][p].second + e.tt;
            v = e.to;
            if (c < dist[v][p+1]) {
                dist[v][p+1] = c;
                if (inq[v][p+1] == 0) {
                    inq[v][p+1] = 1;
                    Q.push(v), P.push(p+1);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 301; j++) {
            if (dist[i][j-1] < dist[i][j])
                dist[i][j] = dist[i][j-1];
        }
    }
}
int main() {
    char s[1024];
    int n, m, q;
    int x, y, c, t;
    int cases = 0;
    while (scanf("%d %d %d", &n, &m, &q) == 3) {
        if (cases++)    puts(".");
        map<string, int> R;

        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            R[s] = i, g[i].clear();
        }
        for (int i = 0; i < m; i++) {
            scanf("%s", s);
            x = R[s];
            scanf("%s", s);
            y = R[s];
            scanf("%d %d", &c, &t);
            g[x].push_back(Edge(y, c, t));
        }
        scanf("%s", s);
        int st = R[s];
        spfa(st, n);
        for (int i = 0; i < q; i++) {
            scanf("%s %d", s, &x), x++;
            y = R[s];
            if (dist[y][x].first != INT_MAX)
                printf("%d %d\n", dist[y][x].first, dist[y][x].second);
            else
                puts("* *");
        }
    }
    return 0;
}