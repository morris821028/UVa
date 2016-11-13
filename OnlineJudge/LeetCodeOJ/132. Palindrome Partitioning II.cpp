class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        vector<vector<char>> isP(n, vector<char>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; i+j < n; j++) {
                if (i == 0) {
                    isP[j][j] = 1;
                } else if (i == 1) {
                    isP[j][j+1] = s[j] == s[j+1];
                } else {
                    isP[j][j+i] = isP[j+1][j+i-1] && s[j] == s[j+i];
                }
            }
        }
        vector<int> dp(n+1, n);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isP[i][j])
                    dp[j+1] = min(dp[j+1], dp[i]+1);
            }
        }
        return dp[n]-1;
    }
};
