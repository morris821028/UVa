class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        for (int i = (1<<n)-1; i >= 0; i--) {
            vector<int> t;
            for (int j = 0; j < n; j++) {
                if ((i>>j)&1) {
                    t.push_back(nums[j]);
                }
            }
            ret.push_back(t);
        }
        return ret;
    }
};
