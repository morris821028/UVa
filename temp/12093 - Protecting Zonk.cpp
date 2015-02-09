#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define MAXN 32767
#define INF 0x3f3f3f3f
vector<int> g[MAXN];
int dp[MAXN][4];
int N, C1, C2, x, y;
void dfs(int u, int p) {
    dp[u][0] = 0; // need 1
    dp[u][1] = 0; // none
    dp[u][2] = INF; // prove 1
    dp[u][3] = INF; // prove 2
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != p) {
            dfs(v, u);
            dp[u][0] += min(dp[v][1], min(dp[v][2], dp[v][3]));
            dp[u][1] += min(dp[v][2], dp[v][3]);
        }
    }
    
    if (g[u].size() > 0) {
        dp[u][2] = dp[u][3] = INF;
        dp[u][3] = C2;
        int sum = 0;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v != p) {
                dp[u][3] += min(dp[v][0], min(dp[v][1], min(dp[v][2], dp[v][3])));
                sum += min(dp[v][1], min(dp[v][2], dp[v][3])); // place
            }
        }
        dp[u][2] = min(dp[u][2], sum + C1);
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v != p) {
                dp[u][2] = min(dp[u][2], sum - min(dp[v][1], min(dp[v][2], dp[v][3])) + dp[v][3]);
            }
        }
    } else {
        dp[u][2] = C1;
        dp[u][3] = C2;
    }
}
int main() {
    while (scanf("%d %d %d", &N, &C1, &C2) == 3 && N) {
        for (int i = 0; i <= N; i++)
            g[i].clear();
        for (int i = 1; i < N; i++) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y), g[y].push_back(x);
        }
        dfs(1, -1);
        int ret = INF;
        for (int i = 1; i < 4; i++) {
            ret = min(ret, dp[1][i]);
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 3
 2 2
 3 3
 3 4
*/