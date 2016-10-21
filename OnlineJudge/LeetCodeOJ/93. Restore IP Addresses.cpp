class Solution {
public:
    string num2str(int x) {
        stringstream sin;
        sin << x;
        return sin.str();
    }
    void dfs(int idx, int i, string &s, string path, vector<string> &ret) {
        if (idx == 4) {
            if (i == s.length()) {
                ret.push_back(path);
            }
            return ;
        }
        if (i == s.length())
            return ;
        int val = 0;
        int f = s[i]-'0';
        for (int t = 0; t < 3 && t+i < s.length(); t++) {
            val = val * 10 + s[t+i]-'0';
            if (t && f == 0)
                return ;
            if (val > 255)
                return ;
            dfs(idx+1, t+i+1, s, path + num2str(val) + (idx != 3 ? "." : ""), ret);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string> ret;
        dfs(0, 0, s, "", ret);
        return ret;
    }
};
