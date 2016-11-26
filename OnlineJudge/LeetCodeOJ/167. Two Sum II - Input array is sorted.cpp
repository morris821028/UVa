class Solution {
public:
    vector<int> twoSum(vector<int>& A, long long target) {
        int n = A.size();
        vector<int> ret;
        for (int l = 0, r = n-1; l < r; l++) {
            while (l < r && A[l] + A[r] > target)
                r--;
            if (l < r && A[l] + A[r] == target) {
                ret.push_back(l+1), ret.push_back(r+1);
                return ret;
            }
        }
        return ret;
    }
};
