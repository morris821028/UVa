#include <stdio.h>
int F[30], C[30];
int ans, V, T, n;
void dfs(int idx, int cost, int vv) {
    if(cost >= ans)
        return;
    if(vv >= V) {
        ans = cost;
        return;
    }
    if(idx == n)
        return;
    dfs(idx+1, cost+C[idx], vv+T*F[idx]);
    dfs(idx+1, cost, vv);
}
int main() {
    int t, i;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d %d", &F[i], &C[i]);
    }
    scanf("%d", &t);
    int cases = 0;
    while(t--) {
        scanf("%d %d", &V, &T);
        ans = 2147483647;
        dfs(0,0,0);
        if(ans != 2147483647)
            printf("Case %d: %d", ++cases, ans);
        else
            printf("Case %d: IMPOSSIBLE", ++cases);
        puts("");
    }
    return 0;
}
