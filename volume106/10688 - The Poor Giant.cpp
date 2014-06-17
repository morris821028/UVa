#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[505][505];
int dfs(int n, int k) {
    int &v = dp[n][k];
    if(v != -1) return v;
    if(n <= 1)  return 0;
    int i, tmp;
    v = 0xfffffff;
    for(i = 1; i <= n; i++) {
        tmp = n*(k+i) + dfs(i-1, k) + dfs(n-i, k+i);
        v = min(v, tmp);
    }
    return v;
}
int main() {
    memset(dp, -1, sizeof(dp));
    int t, cases = 0, n, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        printf("Case %d: %d\n", ++cases, dfs(n, k));
    }
    return 0;
}
