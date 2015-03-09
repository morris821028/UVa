#include <stdio.h>
#include <algorithm>
using namespace std;
double dp[1000][100], dp2[1000], pa[1000][100], pb[1000][100];
double fpa, fpb;
int va[1000][100], vb[1000][100], fva, fvb;
int n, m;
double dfs(int, int);
double dfs2(int idx) {
    if(idx == n)    return fpa*fva + fpb*fvb;
    if(dp2[idx])    return dp2[idx];
    for(int i = 0; i < m; i++)
        dp2[idx] = max(dp2[idx], dfs(idx, i));
    return dp2[idx];
}
double dfs(int idx, int b) {
    if(dp[idx][b])  return dp[idx][b];
    double mx = dfs2(idx+1);
    dp[idx][b] = max(mx, (double)va[idx][b])*pa[idx][b] + max(mx, (double)vb[idx][b])*pb[idx][b];
    return dp[idx][b];
}
int main() {
    int t, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                scanf("%lf %d %lf %d", &pa[i][j], &va[i][j], &pb[i][j], &vb[i][j]);
                dp[i][j] = 0;
            }
            dp2[i] = 0;
        }
        scanf("%lf %d %lf %d", &fpa, &fva, &fpb, &fvb);
        printf("%d\n", (int)dfs2(0));
    }
    return 0;
}
