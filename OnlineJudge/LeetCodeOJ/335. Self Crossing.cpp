class Solution {
public:
    bool isSelfCrossing(vector<int>& A) {
        int n = A.size();
        for (int i = 3; i < n; i++) {
            if (A[i] >= A[i-2] && A[i-1] <= A[i-3])
                return true;
            if (i >= 4 && A[i-1] == A[i-3] && A[i]+A[i-4] >= A[i-2])
                return true;
            if (i >= 5 && A[i-2] >= A[i-4] && A[i]+A[i-4] >= A[i-2] && A[i-1] <= A[i-3] && A[i-1]+A[i-5] >= A[i-3])
                return true;
        }
        return false;
    }
};
