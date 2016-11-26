class Solution {
public:
    int findPeakElement(vector<int>& A) {
        int l = 0, r = A.size()-1;
        int ret = 0;
        while (l < r) {
            int mid = (l + r)/2;
            if (A[mid] < A[mid+1])
                l = mid+1, ret = l;
            else
                r = mid;
        }
        return ret;
    }
};
