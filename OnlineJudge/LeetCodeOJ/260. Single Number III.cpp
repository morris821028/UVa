class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> ret(2, 0);
        int x = 0;
        for (auto e : nums)
            x ^= e;
        int lowbit = x&(-x);
        for (auto e : nums) {
            if (e&lowbit)
                ret[0] ^= e;
            else
                ret[1] ^= e;
        }
        return ret;
    }
};
