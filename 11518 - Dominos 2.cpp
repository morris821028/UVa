#include <cstdio>
#include <vector>
using namespace std;
vector<int> g[10005];
int used[10005];
void dfs(int nd) {
    used[nd] = 1;
    int i;
    for(i = g[nd].size()-1; i >= 0; i--) {
        if(!used[g[nd][i]]) {
            dfs(g[nd][i]);
        }
    }
}
int main() {
    int t, n, m, l;
    int i, st, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &m, &l);
        for(i = 0; i <= n; i++)
            g[i].clear(), used[i] = 0;
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
        }
        while(l--) {
            scanf("%d", &st);
            dfs(st);
        }
        int cnt = 0;
        for(i = 0; i <= n; i++)
            cnt += used[i];
        printf("%d\n", cnt);
    }
    return 0;
}
