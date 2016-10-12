class Solution {
public:
    void sortColors(vector<int>& nums) {
        int cnt[3] = {};
        for (auto e : nums)
            cnt[e]++;
        
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = cnt[i]-1; j >= 0; j--)
                nums[index++] = i;
        }
    }
};
