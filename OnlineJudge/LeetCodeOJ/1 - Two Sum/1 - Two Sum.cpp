class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> R;
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            if (R.count(target - nums[i])) {
                ret.push_back(R[target - nums[i]]);
                ret.push_back(i+1);
                return ret;
            }
            R[nums[i]] = i+1;
        }
        return ret;
    }
};
