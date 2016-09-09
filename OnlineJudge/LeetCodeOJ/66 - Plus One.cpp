class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> A = digits;
        if (A.size() == 0)
            return A;
        int n = A.size();
        A[n-1]++;
        for (int i = n-1; i >= 1; i--) {
            if (A[i] >= 10)
                A[i-1]++, A[i] -= 10;
        }
        if (A[0] >= 10) {
            vector<int> B(n+1, 0);
            for (int i = 0; i < n; i++)
                B[i+1] = A[i];
            B[0] = 1, B[1] -= 10;
            A = B;
        }
        return A;
    }
};
