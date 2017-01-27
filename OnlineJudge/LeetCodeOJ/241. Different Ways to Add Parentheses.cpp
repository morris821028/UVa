class Solution {
public:
    static int add(int x, int y) {return x + y;}
    static int sub(int x, int y) {return x - y;}
    static int mul(int x, int y) {return x * y;}
    vector<int> dfs(int l, int r, string &s) {
        vector<int> ret;
        for (int i = l; i <= r; i++) {
            if (s[i] == '+' || s[i] == '-' || s[i] == '*') {
                vector<int> L(dfs(l, i-1, s)), R(dfs(i+1, r, s));
                int (*f[])(int, int) = {add, sub, mul};
                int idx = 0;
                if (s[i] == '-')
                    idx = 1;
                else if (s[i] == '*')
                    idx = 2;
                for (auto a : L) {
                    for (auto b : R) {
                        ret.push_back(f[idx](a, b));
                    }
                }
            }
        }
        if (ret.size() == 0) {
            int x = 0;
            for (int i = l; i <= r; i++)
                x = x * 10 + s[i] - '0';
            ret.push_back(x);
        }
        return ret;
    }
    vector<int> diffWaysToCompute(string input) {
        return dfs(0, input.size()-1, input);
    }
};
