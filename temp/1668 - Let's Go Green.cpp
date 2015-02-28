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
// greedy, tree dp
#define MAXN 100005
vector< pair<int, int> > g[MAXN];
int ret = 0;
void dfs(int u, int p, int pw) {
    int mx = pw, sum = pw;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i].first;
        if (v == p)
            continue;
        dfs(v, u, g[u][i].second);
        mx = max(mx, g[u][i].second);
        sum += g[u][i].second;
    }
    if (mx * 2 >= sum) {
        ret += mx - pw;         // exactly generate #mx-pw path, with connected or no connected.
    } else {
        ret += (sum+1)/2 - pw;  // pair banch connect(completed path), reserve #pw to parent.
    }
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
        ret = 0;
        dfs(1, -1, 0);
        printf("Case #%d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
 2
 5
 1 2 2
 2 3 1
 3 4 2
 3 5 1
 7
 1 2 1
 2 3 2
 2 4 1
 2 5 3
 5 6 2
 5 7 3
 */
