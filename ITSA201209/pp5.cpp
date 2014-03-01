#include <stdio.h>
#include <algorithm>
#include <vector>
#define oo 0xfffffff
using namespace std;
vector<int> edge[95005];
int dp_down[95005][2], dp_up[95005];
int used[95005];
void dfs(int nd) {
    for(vector<int>::iterator i = edge[nd].begin(); i != edge[nd].end(); i++) {
        if(used[*i] == 0) {
            used[*i] = 1;
            dfs(*i);
            if(dp_down[*i][0]+1 > dp_down[nd][1])
                dp_down[nd][1] = dp_down[*i][0]+1;
            if(dp_down[nd][1] > dp_down[nd][0])
                swap(dp_down[nd][0], dp_down[nd][1]);
        }
    }
}
void dfs2(int nd, int v) {
    dp_up[nd] = v;
    for(vector<int>::iterator i = edge[nd].begin(); i != edge[nd].end(); i++) {
        if(used[*i] == 0) {
            used[*i] = 1;
            int hv;
            if(dp_down[*i][0]+1 != dp_down[nd][0])
                hv = dp_down[nd][0];
            else
                hv = dp_down[nd][1];
            hv = max(hv, dp_up[nd]);
            dfs2(*i, hv+1);
        }
    }
}
int main() {
    int n, m, i, y;
    while(scanf("%d", &n) == 1) {
        for(i = 1; i <= n; i++) {
            edge[i].clear();
            dp_down[i][0] = 0;
            dp_down[i][1] = 0;
            dp_up[i] = 0;
            used[i] = 0;
        }
        int x, y;
        for(i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            x++, y++;
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        used[1] = 1;
        dfs(1);
        for(i = 1; i <= n; i++) used[i] = 0;
        used[1] = 1;
        dfs2(1, 0);
        int root[95001], best = oo;
        for(i = 1; i <= n; i++) {
            root[i] = max(max(dp_down[i][0], dp_down[i][1]), dp_up[i]);
            best = min(best, root[i]);
        }
        for(i = 1; i <= n; i++)
            if(root[i] == best) {
                printf("%d\n", i-1);
                break;
            }
    }
    return 0;
}
