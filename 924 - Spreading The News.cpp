#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int E, T, i, n, x;
    while(scanf("%d", &E) == 1) {
        vector<int> Link[E];
        for(i = 0; i < E; i++) {
            Link[i].clear();
            scanf("%d", &n);
            while(n--) {
                scanf("%d", &x);
                Link[i].push_back(x);
            }
        }
        scanf("%d", &T);
        while(T--) {
            scanf("%d", &x);
            int dp[E], used[E], cnt[E+1];
            memset(dp, 0, sizeof(dp));
            memset(cnt, 0, sizeof(cnt));
            memset(used, 0, sizeof(used));
            used[x] = 1;
            queue<int> Q;
            Q.push(x);
            while(!Q.empty()) {
                x = Q.front();
                Q.pop();
                for(vector<int>::iterator i = Link[x].begin(); i != Link[x].end(); i++) {
                    if(used[*i] == 0) {
                        used[*i] = 1;
                        Q.push(*i);
                        dp[*i] = dp[x]+1;
                        cnt[dp[*i]]++;
                    }
                }
            }
            int M = 0, D;
            for(i = 1; i <= E; i++) {
                if(cnt[i] > M) {
                    M = cnt[i];
                    D = i;
                }
            }
            if(M)
                printf("%d %d\n", M, D);
            else
                puts("0");
        }
    }
    return 0;
}
