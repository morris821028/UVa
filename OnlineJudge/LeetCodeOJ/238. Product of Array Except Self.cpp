class Solution {
public:
    vector<int> productExceptSelf(vector<int>& A) {
        int n = A.size();
        vector<int> ret(n);
        for (int i = 0, v = 1; i < n; i++) {
            ret[i] = v, v *= A[i];
        }
        for (int i = n-1, v = 1; i >= 0; i--) {
            ret[i] *= v, v *= A[i];
        }
        return ret;
    }
};
