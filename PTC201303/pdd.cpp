#include <stdio.h>
#include <vector>
#include <stdlib.h>
using namespace std;
int d[30], n;
int i, j;
int g[30][30], ans;
int used[30] = {};
vector<int> vg[30];
void dfs(int idx, int sum) {
    if(sum >= ans)
        return ;
    if(idx == n) {
        int tmp = 0, v = 0;
        for(i = 0; i < n; i++) {
            if(d[i])
                continue;
            v = 0;
            for(j = 0; j < vg[i].size(); j++) {
                v |= d[vg[i][j]];
            }
            if(v != 3)
                return;
        }
        ans = sum;
        return ;
    }
    d[idx] = 0;
    dfs(idx+1, sum);
    d[idx] = 1;
    dfs(idx+1, sum+1);
    d[idx] = 2;
    dfs(idx+1, sum+1);
    d[idx] = 3;
    dfs(idx+1, sum+2);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            vg[i].clear();
            for(j = 0; j < n; j++) {
                scanf("%d", &g[i][j]);
                if(g[i][j])
                    vg[i].push_back(j);
            }
        }
        ans = 0xffffff;
        dfs(0, 0);
        printf("%d\n", ans);
    }
    puts("");
    return 0;
}
/*
2
3
0 1 1
1 0 1
1 1 0
10
0 1 0 1 0 0 0 0 1 1
1 0 0 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0 1 0
1 0 1 0 0 0 0 0 1 0
0 0 0 0 0 1 0 0 0 1
0 0 0 0 1 0 0 1 1 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 1 1 0 0 0
1 1 1 1 0 1 0 0 0 0
1 0 0 0 1 0 0 0 0 0
*/
