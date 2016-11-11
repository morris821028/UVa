class Solution {
public:
    void dfs(int l, int r, vector<string> path, vector<vector<char>> &dp, 
        string &s, vector<vector<string>> &ret) {
        if (l > r) {
            ret.push_back(path);
            return ;
        }
        for (int i = l; i <= r; i++) {
            if (dp[l][i]) {
                path.push_back(s.substr(l, i-l+1));
                dfs(i+1, r, path, dp, s, ret);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<char>> dp(n, vector<char>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + i < n; j++) {
                if (i == 0) {
                    dp[j][j] = 1;
                } else if (i == 1) {
                    dp[j][j+1] = s[j] == s[j+1];
                } else {
                    dp[j][j+i] = dp[j+1][j+i-1] && s[j] == s[j+i];
                }
            }
        }
        
        vector<vector<string>> ret;
        dfs(0, n-1, vector<string>(), dp, s, ret);
        return ret;
    }
};
