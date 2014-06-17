#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
vector<int> Link[201];
int color[201], access = 1, cnt, total;
void dfs(int nd) {
    total++;
    if(color[nd] == 1)
        cnt++;
    if(!access)
        return;
    for(vector<int>::iterator i = Link[nd].begin(); i != Link[nd].end(); i++) {
        if(color[*i] == color[nd])
            access = 0;
        else if(color[*i] == 0) {
            color[*i] = 3-color[nd];
            dfs(*i);
        }
    }
}
int main() {
    int t, n, m, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            Link[i].clear();
        while(m--) {
            scanf("%d %d", &i, &j);
            Link[i].push_back(j);
            Link[j].push_back(i);
        }
        memset(color, 0, sizeof(color));
        int ans = 0;
        access = 1;
        for(i = 0; i < n; i++) {
            if(color[i] == 0 && access == 1) {
                access = 1;
                color[i] = 1;
                cnt = 0, total = 0;
                dfs(i);
                if(cnt > total - cnt && total > 1)
                    cnt = total - cnt;
                ans += cnt;
            }
        }
        if(access) {
            printf("%d\n", ans);
        } else {
            puts("-1");
        }
    }
    return 0;
}
