#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

struct Edge {
    int from, to;
    int64_t c;
    Edge(int from=0, int to=0, int64_t c=0):
    from(from), to(to), c(c) {}
};

const int MAXN = 50005;
static vector<Edge> g[MAXN];
static int indeg[MAXN];
static int64_t toST[MAXN], diffST[MAXN];
static int64_t toED[MAXN], diffED[MAXN];
static vector<int> order;
static vector<Edge> in;
static int n;
void topo() {
    memset(toST, 0, sizeof(toST));
    memset(diffST, 0, sizeof(diffST));
    memset(toED, 0, sizeof(toED));
    memset(diffED, 0, sizeof(diffED));
    order.clear();
    
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0)
            Q.push(i);
    }
    
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        order.push_back(u);
        for (auto e : g[u]) {
            if (toST[e.to] && toST[e.to] != toST[u] + e.c)
                diffST[e.to]++;
            diffST[e.to] = diffST[e.to] + diffST[u];
            toST[e.to] = max(toST[e.to], toST[u] + e.c);
            if (--indeg[e.to] == 0)
                Q.push(e.to);
        }
    }
    assert(order.size() == n);
    for (int i = (int) order.size()-1; i >= 0; i--) {
        int u = order[i];
        if (u == n)
            continue;
        for (auto e : g[u]) {
            toED[u] = max(toED[u], toED[e.to] + e.c);
            diffED[u] += diffED[e.to];
        }
        
        if (g[u].size()) {
            Edge e = g[u][0];
            int64_t dd = toED[e.to] + e.c;
            for (int j = 1; j < g[u].size(); j++)
                diffED[u] += (toED[g[u][j].to] + g[u][j].c != dd);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (diffST[i] > 0 && diffED[i] > 0) {
            puts("No solution");
            return ;
        }
    }
    
    vector< pair<int, int64_t> > ret;
    for (int i = 0; i < in.size(); i++) {
        Edge e = in[i];
        if (diffST[e.from] == 0 && diffST[e.to] > 0) {
            int64_t cc = toST[n] - (toST[e.from] + toED[e.to] + e.c);
            assert(cc >= 0);
            if (cc > 0)
                ret.push_back(make_pair(i+1, cc));
        }
    }
    
    printf("%d %lld\n", (int) ret.size(), toST[n]);
    for (auto e : ret)
        printf("%d %lld\n", e.first, e.second);
}
int main() {
    int cases = 0;
    int m;
    while (scanf("%d %d", &n, &m) == 2 && n) {
        for (int i = 0; i <= n; i++)
            g[i].clear();
        in.clear();
        memset(indeg, 0, sizeof(indeg));
        
        for (int i = 0; i < m; i++) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            g[x].push_back(Edge(x, y, c));
            in.push_back(Edge(x, y, c));
            indeg[y]++;
        }
        
        printf("Case %d: ", ++cases);
        
        topo();
    }
    return 0;
}
/*
 3 3
 1 3 10
 1 2 3
 2 3 5
 4 5
 1 3 5
 3 2 1
 2 4 6
 1 4 10
 3 4 3
 3 4
 1 2 1
 1 2 2
 2 3 1
 2 3 2
 0 0
*/
