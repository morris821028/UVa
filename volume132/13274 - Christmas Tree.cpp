#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

static const int MAXN = 1024;
static vector<int> g[MAXN];

int dfs(int p, int u, int m) {
    if (g[u].size() < m)
        return 1;
    int ret = 1, t = 0;
    vector<int> A(g[u].size());
    for (auto v: g[u]) {
        if (v == p)
            continue;
        A[t] = dfs(u, v, m), t++;
    }
    if (t < m)
        return 1;
    sort(A.begin(), A.begin()+t);
    for (int i = t-1; m > 0; i--, m--)
        ret += A[i];
    return ret;
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
            g[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        int ret = dfs(-1, 1, m);
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
 2
 6 3
 1 2
 1 3
 1 4
 4 5
 4 6
 6 4
 1 2
 1 3
 1 4
 4 5
 4 6
*/
