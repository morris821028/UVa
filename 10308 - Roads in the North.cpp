#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct ele {
    int to, v;
};
vector<ele> g[10001];
int dp1[10001][2], dp2[10001];
void init() {
    static int i;
    for(i = 1; i <= 10000; i++)
        g[i].clear(), dp1[i][0] = dp1[i][1] = dp2[i] = 0;
}
void dfs1(int nd, int p) {
    for(vector<ele>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(it->to != p) {
            dfs1(it->to, nd);
            if(dp1[it->to][0] + it->v > dp1[nd][1])
                dp1[nd][1] = dp1[it->to][0] + it->v;
            if(dp1[nd][1] > dp1[nd][0])
                swap(dp1[nd][0], dp1[nd][1]);
        }
    }
}
void dfs2(int nd, int p, int st, int w) {
    if(nd != st) {
        if(dp1[nd][0] + w == dp1[p][0])
            dp2[nd] = max(dp2[p], dp1[p][1])+w;
        else
            dp2[nd] = max(dp2[p], dp1[p][0])+w;
    }
    for(vector<ele>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(it->to != p) {
            dfs2(it->to, nd, st, it->v);
        }
    }
}
void sol(int st) {
    dfs1(st, -1);
    dfs2(st, -1, st, 0);
    int ans = 0, i;
    for(i = 1; i <= 10000; i++) {
        ans = max(ans, dp1[i][0]+dp1[i][1]);
        ans = max(ans, dp1[i][0]+dp2[i]);
    }
    printf("%d\n", ans);
}
int main() {
    char cmd[100];
    ele E;
    int x, y, v;
    while(gets(cmd)) {
        if(cmd[0] == '\0') {
            sol(x);
            init();
            continue;
        }
        sscanf(cmd, "%d %d %d", &x, &y, &v);
        E.to = x, E.v = v;
        g[y].push_back(E);
        E.to = y;
        g[x].push_back(E);
    }
    sol(x);
    return 0;
}
