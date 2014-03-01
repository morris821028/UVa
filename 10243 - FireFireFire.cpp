#include <stdio.h>
#include <vector>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;
struct Arc {
    int to;
};
vector<Arc> nd[1001];
int dp[1001][2], used[1001];
void dfs(int node) {
    used[node] = 1;
    dp[node][0] = 0;
    dp[node][1] = 1;
    int i;
    for(vector<Arc>::iterator i = nd[node].begin(); i != nd[node].end(); i++) {
        if(used[i->to] == 0) {
            dfs(i->to);
            dp[node][0] += dp[i->to][1];
            dp[node][1] += min(dp[i->to][0], dp[i->to][1]);
        }
    }
}
int main() {
    int n, i, m, y;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 1; i <= n; i++)
            nd[i].clear(), used[i] = 0;
        Arc tmp;
        for(i = 1; i <= n; i++) {
            scanf("%d", &m);
            while(m--) {
                scanf("%d", &tmp.to);
                nd[i].push_back(tmp);
            }
        }
        dfs(1);
        int ans = min(dp[1][0], dp[1][1]);
        if(n == 1)  ans = 1;
        printf("%d\n", ans);
    }
    return 0;
}
