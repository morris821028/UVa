class Solution {
public:
    bool canJump(vector<int>& nums) {
        int ret = 0;
        for (int i = 0; i < nums.size() && ret >= i; i++) {
            if (nums[i] + i >= ret)
                ret = nums[i] + i;
        }
        return ret >= nums.size()-1;
    }
};
