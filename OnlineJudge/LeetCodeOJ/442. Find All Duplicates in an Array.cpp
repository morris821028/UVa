class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] && nums[i] != i+1) {
                int x = nums[i];
                if (nums[x-1] == x) {
                    nums[i] = 0;
                    ret.push_back(x);
                    break;
                } else {
                    swap(nums[x-1], nums[i]);
                }
            }
        }
        return ret;
    }
};
