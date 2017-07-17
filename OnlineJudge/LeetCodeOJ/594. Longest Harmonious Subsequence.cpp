class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> A;
        int ret = 0;
        for (auto x : nums) {
            A[x]++;
        }
        
        for (auto x : A) {
            int val = x.first;
            int cnt = x.second;
            if (A.count(val+1)) {
                cnt += A[val+1];
                ret = max(ret, cnt);
            }
        }
        return ret;
    }
};
