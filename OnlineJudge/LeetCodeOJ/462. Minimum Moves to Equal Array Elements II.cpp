class Solution {
public:
    int minMoves2(vector<int>& A) {
        sort(A.begin(), A.end());
        int n = A.size();
        int mid = A[n/2];
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret += abs(mid - A[i]);
        return ret;
    }
};
