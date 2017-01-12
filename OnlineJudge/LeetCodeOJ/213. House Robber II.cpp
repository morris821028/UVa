class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0)
            return 0;
        int p0 = 0, p1 = 0;
        int ret = 0;
        for (int i = 1; i < n; i++) {
            int q0, q1;
            q0 = max(p0, p1);
            q1 = p0 + nums[i];
            p0 = q0, p1 = q1;
        }
        ret = max(p0, p1);
        p0 = 0, p1 = nums[0];
        for (int i = 1; i < n; i++) {
            int q0, q1;
            q0 = max(p0, p1);
            q1 = p0 + nums[i];
            p0 = q0, p1 = q1;
        }
        if (n == 1)
            ret = max(ret, p1);
        else
            ret = max(ret, p0);
        return ret;
    }
};
