class Solution {
public:
    int minPatches(vector<int>& A, int n) {
        sort(A.begin(), A.end());
        int ret = 0;
        long long r = 0, i = 0, m = A.size();
        while (r < n && i < m) {
            if (A[i] > r+1) {
                ret ++, r += (r+1);
            } else {
                r += A[i], i++;
            }
        }
        while (r < n)
            r += (r+1), ret++;
        return ret;
    }
};
