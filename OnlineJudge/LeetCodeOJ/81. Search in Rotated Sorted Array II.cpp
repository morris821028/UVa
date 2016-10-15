class Solution {
public:
    bool search(vector<int>& A, int target) {
        int l = 0, r = A.size()-1, mid;
        while (l <= r) {
            mid = (l + r)/2;
            if (A[mid] == target || A[l] == target || A[r] == target)
                return true;
            if (A[mid] > A[l]) {
                if (target >= A[l] && target < A[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            } else if (A[mid] < A[r]) {
                if (target <= A[r] && target > A[mid])
                    l = mid + 1;
                else
                    r = mid - 1;
            } else {
                l++;
            }
        }
        return false;
    }
};
