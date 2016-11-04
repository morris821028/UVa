class Solution {
public:
    int minimumTotal(vector<vector<int>>& A) {
        int n = A.size();
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                int l = (j-1 >= 0) ? A[i-1][j-1] : INT_MAX;
                int r = (j < i) ? A[i-1][j] : INT_MAX;
                A[i][j] = min(l, r) + A[i][j];
            }
        }
        
        int ret = INT_MAX;
        for (int i = 0; i < n; i++)
            ret = min(ret, A[n-1][i]);
        return ret;
    }
};
