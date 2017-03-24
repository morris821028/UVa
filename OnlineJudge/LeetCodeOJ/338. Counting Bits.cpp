class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ret(n+1, 0);
        for (int i = 1; i <= n; i++) {
            ret[i] = ret[i>>1] + (i&1);
        }
        return ret;
    }
};
