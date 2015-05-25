class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        vector<int> v = nums;
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        return v.size() < nums.size();
    }
};