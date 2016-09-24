class Solution {
public:
    void dfs(string s, int idx, int n, int used[], int k, int f[], string &ret) {
        if (idx == n) {
            ret = s;
            return ;
        }
        for (int i = 1; i <= n; i++) {
            if (used[i])    continue;
            if (f[n-1-idx] < k) {
                k -= f[n-1-idx];
                continue;
            }
            used[i] = 1;
            dfs(s + (char)(i+'0'), idx+1, n, used, k, f, ret);
            return ;
        }
    }
    string getPermutation(int n, int k) {
        int used[10] = {}, f[10] = {};
        string ret = "";
        f[0] = 1;
        for (int i = 1; i < 10; i++)
            f[i] = f[i-1] * i;
        dfs("", 0, n, used, k, f, ret);
        return ret;
    }
};
