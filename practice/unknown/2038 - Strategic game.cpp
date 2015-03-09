#include <stdio.h>
#include <vector>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;
struct Arc {
    int to;
};
vector<Arc> nd[2000];
int dp[2000][2], used[2000];
int dfs(int node) {
    used[node] = 1;
    dp[node][0] = 0;
    dp[node][1] = 1;
    for(vector<Arc>::iterator i = nd[node].begin(); i != nd[node].end(); i++) {
        if(used[i->to] == 0) {
            dfs(i->to);
            dp[node][0] += dp[i->to][1];
            dp[node][1] += min(dp[i->to][0], dp[i->to][1]);
        }
    }
    return min(dp[node][0], dp[node][1]);
}
int main() {
    int n, m, st, ed, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            nd[i].clear(), used[i] = 0;
        Arc tmp;
        for(i = 0; i < n; i++) {
            scanf("%d: (%d)", &st, &m);
            while(m--) {
                scanf("%d", &ed);
                tmp.to = ed;
                nd[st].push_back(tmp);
                tmp.to = st;
                nd[ed].push_back(tmp);
            }
        }
        printf("%d\n", dfs(0));
    }
    return 0;
}
