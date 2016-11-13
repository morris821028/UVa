class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int v[32][3] = {};
        for (auto e : nums) {
            unsigned int x = e;
            for (int i = 0; i < 32; i++)
                v[i][x%3]++, x = x/3;
        }
        unsigned int ret = 0;
        for (int i = 31; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                if (v[i][j]%3)
                    ret = ret * 3 + j;
            }
        }
        return ret;
    }
};
