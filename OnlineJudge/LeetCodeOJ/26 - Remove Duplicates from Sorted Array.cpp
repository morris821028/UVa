class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
        return nums.size();
    }
};
