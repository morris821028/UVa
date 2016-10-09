class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        int n = A.size();
        int sum = 0, sum2 = 0;
        for (int i = 0; i < n; i++)
            sum += A[i] * i, sum2 += A[i];
        int ret = sum;
        for (int i = n-1; i >= 0; i--) {
            sum -= n * A[i];
            sum += sum2;
            ret = max(ret, sum);
        }
        return ret;
    }
};
