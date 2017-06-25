class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> A;
        int ret = 0;
        for (auto x : nums) {
            int mx = 1;
            unordered_map<int, int>::iterator it;
            it = A.find(x-1);
            if (it != A.end())  mx = max(mx, it->second+1);
            it = A.find(x);
            if (it != A.end())  mx = max(mx, it->second+1);
            it = A.find(x+1);
            if (it != A.end())  mx = max(mx, it->second+1);
            ret = max(ret, mx);
            A[x] = mx;
        }
        return ret;
    }
};
