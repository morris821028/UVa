#include <stdio.h>
#define maxN 50005
int min(int x, int y) {
    return x < y ? x : y;
}
int used[maxN], dp[maxN], send[maxN];
int in_stk[maxN], stk[maxN], stkIdx;
int vfind[maxN], fdIdx;
int lead[maxN];
int dfs(int nd) {
    used[nd] = in_stk[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++fdIdx;
    int mn = vfind[nd];
    if(!used[send[nd]])
        mn = min(mn, dfs(send[nd]));
    if(in_stk[send[nd]])
        mn = min(mn, vfind[send[nd]]);
    if(mn == vfind[nd]) {
        int cnt = -1;
        do {
            lead[stk[stkIdx]] = nd;
            in_stk[stk[stkIdx]] = 0;
            cnt++;
        } while(stk[stkIdx--] != nd);
        if(cnt > 0)
            dp[nd] += cnt;
        else
            dp[nd] += dp[lead[send[nd]]];
    }
    return mn;
}
int main() {
    int n, t, i, j;
    int cases = 0;

    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int u, v;
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &u, &v);
            send[u] = v;
            used[i] = in_stk[i] = 0;
            dp[i] = 1;
            lead[i] = i;
        }
        int ans = -1, an;
        for(i = 1; i <= n; i++) {
            if(!used[i]) {
                fdIdx = 0, stkIdx = -1;
                dfs(i);
            }
        }
        for(i = 1; i <= n; i++) {
            if(dp[i] > ans)
                ans = dp[i], an = i;
        }
        printf("Case %d: %d\n", ++cases, an);
    }
    return 0;
}
