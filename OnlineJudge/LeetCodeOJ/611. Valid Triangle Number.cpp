class Solution {
public:
    int triangleNumber(vector<int>& A) {
        sort(A.begin(), A.end());
        int ret = 0, n = A.size();
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = i+1; j < n; j++) {
                int a = A[i], b = A[j];
                int t = (upper_bound(A.begin(), A.end(), a+b-1) - A.begin());
                if (t > j) {
                    ret += t - j - 1;
                }
            }
        }
        return ret;
    }
};
