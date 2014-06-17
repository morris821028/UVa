#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
vector<int> g[1005], dag[1005];
int vfind[1005], findIdx;
int stk[1005], stkIdx;
int in_stk[1005], visited[1005];
int contract[1005];
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(int i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i]])
            mn = min(mn, scc(g[nd][i]));
        if(in_stk[g[nd][i]])
            mn = min(mn, vfind[g[nd][i]]);
    }
    if(mn == vfind[nd]) {
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int dp[1005], contSize[1005];
int dfs(int nd) {
    if(dp[nd])  return dp[nd];
    int ret = 0;
    for(int i = 0; i < dag[nd].size(); i++)
        ret = max(ret, dfs(dag[nd][i]));
    dp[nd] = ret + contSize[nd];
    return dp[nd];
}
int main() {
    int testcase, n, m;
    int x, y, i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++) {
            g[i].clear();
            dag[i].clear();
        }
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
        }
        // SCC
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        for(i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        memset(dp, 0, sizeof(dp));
        memset(contSize, 0, sizeof(contSize));
        for(i = 1; i <= n; i++) {
            x = contract[i];
            contSize[x]++;
            for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++) {
                y = contract[*it];
                if(x != y)
                    dag[x].push_back(y);
            }
        }
        // dp for a longest path
        int ret = 0;
        for(i = 1; i <= n; i++)
            ret = max(ret, dfs(contract[i]));
        printf("%d\n", ret);
    }
    return 0;
}
