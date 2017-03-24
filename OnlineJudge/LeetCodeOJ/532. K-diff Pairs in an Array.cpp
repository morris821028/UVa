class Solution {
public:
    int findPairs(vector<int>& A, int k) {
        sort(A.begin(), A.end());
        int n = A.size(), ret = 0;
        for (int i = 0, j = 1; i < n && j < n; i++) {
            if (i && A[i] == A[i-1])
                continue;
            if (j <= i) j = i+1;
            while (j < n && A[j]-k < A[i])
                j++;
            if (j < n && A[j]-k == A[i])
                ret++;
        }
        return ret;
    }
};
