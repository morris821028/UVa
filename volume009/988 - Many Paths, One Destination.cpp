#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int main() {
    int n;
    int first = 0;
    while(scanf("%d", &n) == 1) {
        int i, j, k;
        int indeg[1000] = {}, outdeg[1000];
        vector<int> g[1000];
        for(i = 0; i < n; i++) {
            scanf("%d", &outdeg[i]);
            for(j = 0; j < outdeg[i]; j++)
                scanf("%d", &k), g[i].push_back(k), indeg[k]++;
        }
        int dp[1000] = {};
        dp[0] = 1;
        queue<int> Q;
        Q.push(0);
        while(!Q.empty()) {
            k = Q.front();
            Q.pop();
            for(i = 0; i < g[k].size(); i++) {
                dp[g[k][i]] += dp[k];
                indeg[g[k][i]]--;
                if(indeg[g[k][i]] == 0)
                    Q.push(g[k][i]);
            }
        }
        int ans = 0;
        for(i = 0; i < n; i++)
            if(outdeg[i] == 0)
                ans += dp[i];
        if(first)   puts("");
        first = 1;
        printf("%d\n", ans);
    }
    return 0;
}
