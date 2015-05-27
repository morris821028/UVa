class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int pos = (int) (lower_bound(nums.begin(), nums.end(), target) - nums.begin());
        return pos;
    }
};
