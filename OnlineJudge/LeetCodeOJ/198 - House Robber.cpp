class Solution {
public:
    int rob(vector<int>& nums) {
        int a = 0, b = 0;   // not have, have
        for (int i = 0; i < nums.size(); i++) {
            int ta, tb;
            ta = max(a, b);
            tb = max(a+nums[i], b);
            a = ta, b = tb;
        }
        return max(a, b);
    }
};
