class Solution {
public:
    int dp[1<<20];
    int dfs(int u, int n, int m) {
        if (m <= 0)
            return 0;
        if (dp[u] != -1)
            return dp[u];
        int &ret = dp[u];
        ret = 0;
        for (int i = 0; i < n && ret == 0; i++) {
            if ((u>>i)&1) {
                ret |= !dfs(u^(1<<i), n, m-(i+1));
            }
        }
        return ret;
    }
    bool canIWin(int n, int m) {
        if (m == 0)
            return 1;
        if ((n)*(n+1)/2 < m)
            return 0;
        memset(dp, -1, sizeof(dp[0])*(1<<n));
        return dfs((1<<n)-1, n, m);
    }
};
