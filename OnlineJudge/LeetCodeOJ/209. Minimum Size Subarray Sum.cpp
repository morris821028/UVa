class Solution {
public:
    int minSubArrayLen(int s, vector<int>& A) {
        int n = A.size();
        int l = -1, sum = 0, ret = INT_MAX;
        for (int r = 0; r < n; r++) {
            sum += A[r];
            while (l+1 < r && sum - A[l+1] >= s)
                l++, sum -= A[l];
            if (sum >= s)
                ret = min(ret, r-l);
        }
        return ret == INT_MAX ? 0 : ret;
    }
};
