class Solution {
public:
    int findRadius(vector<int>& A, vector<int>& B) {
        long long l = 0, r = INT_MAX;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        int n = A.size(), m = B.size();
        int ret = 0;
        while (l <= r)  {
            long long mid = (l+r)/2;
            int ok = 1;
            for (int i = 0, j = 0; i < n && ok; i++) {
                long long x = A[i];
                while (j < m && (B[j]-mid > x || B[j]+mid < x))
                    j++;
                ok &= j < m && (B[j]-mid <= x && B[j]+mid >= x);
            }
            if (ok)
                r = mid-1, ret = mid;
            else
                l = mid+1;
        }
        return ret;
    }
};
