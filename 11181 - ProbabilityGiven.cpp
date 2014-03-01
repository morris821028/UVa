#include <stdio.h>
double p[20], res[20] = {}, ans, tot;
int n, r, used[20] = {};
void dfs(int idx, int c) {
    if(c+n-idx < r)    return;
    if(c == r) {
        double rp = 1;
        int i;
        for(i = 0; i < n; i++) {
            if(used[i])
                rp *= p[i];
            else
                rp *= (1-p[i]);
        }
        for(i = 0; i < n; i++)
            if(used[i])
                res[i] += rp;
        tot += rp;
        return;
    }
    used[idx] = 1;
    dfs(idx+1, c+1);
    used[idx] = 0;
    dfs(idx+1, c);
}
void sol() {
    int i, j, k;
    for(i = 0; i < n ;i++) {
        scanf("%lf", &p[i]);
        res[i] = 0;
    }
    tot = 0;
    dfs(0, 0);
    for(i = 0; i < n; i++)
        printf("%.6lf\n", res[i]/tot);
}
int main() {
    int cases = 0;
    while(scanf("%d %d", &n, &r)) {
        if(n == 0 && r == 0)
            break;
        printf("Case %d:\n", ++cases);
        sol();
    }
    return 0;
}
