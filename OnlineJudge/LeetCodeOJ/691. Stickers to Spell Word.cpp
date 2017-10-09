class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        const int n = (int) target.length();
        int dp[1<<n];
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 0; i < (1<<n); i++) {
            if (dp[i] == 0x3f3f3f3f)
                continue;
            for (auto e : stickers) {
                int mask = i;
                for (auto c : e) {
                    for (int k = 0; k < n; k++) {
                        if (((mask>>k)&1) == 0 && target[k] == c) {
                            mask |= 1<<k;
                            break;
                        }
                    }
                    dp[mask] = min(dp[mask], dp[i]+1);
                }
            }
        }
        if (dp[(1<<n)-1] == 0x3f3f3f3f)
            return -1;
        return dp[(1<<n)-1];
    }
};
