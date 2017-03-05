class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size(), sum = 0;
        for (auto e : nums)
            sum += e;
        return n * (n+1) / 2 - sum;
    }
};
