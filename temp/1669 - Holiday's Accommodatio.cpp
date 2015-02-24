#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <vector>
using namespace std;
#define MAXN 262144
vector< pair<int, int> > g[MAXN];
int visited[MAXN], parent[MAXN], tree[MAXN];
void solve(int N) {
    for (int i = 0; i <= N; i++)
        visited[i] = 0;
    queue<int> Q;
    vector<int> A;
    int u, v;
    Q.push(1), visited[1] = 1, parent[1] = -1;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        A.push_back(u);
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first;
            if (visited[v] == 0) {
                visited[v] = 1;
                Q.push(v), parent[v] = u;
            }
        }
    }
    for (int i = (int) A.size() - 1; i >= 0; i--) {
        u = A[i];
        int sz = 1;
        for (int j = 0; j < g[u].size(); j++) {
            v = g[u][j].first;
            if (v == parent[u])
                continue;
            sz += tree[v];
        }
        tree[u] = sz;
    }
    long long ret = 0;
    for (int i = 1; i <= N; i++) {
        u = i;
        for (int j = 0; j < g[u].size(); j++) {
            v = g[u][j].first;
            if (v == parent[u])
                continue;
            int pass = min(tree[v], N - tree[v]) * 2; // in&out
            ret += (long long) g[u][j].second * pass;
        }
    }
    printf("%lld\n", ret);
}
int main() {
    int testcase, cases = 0;
    int N, x, y, v;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i <= N; i++)
            g[i].clear();
        for (int i = 1; i < N; i++) {
            scanf("%d %d %d", &x, &y, &v);
            g[x].push_back(make_pair(y, v));
            g[y].push_back(make_pair(x, v));
        }
        printf("Case #%d: ", ++cases);
        solve(N);
    }
    return 0;
}
/*
 2
 4
 1 2 3
 2 3 2
 4 3 2
 6
 1 2 3
 2 3 4
 2 4 1
 4 5 8
 5 6 5
 */
