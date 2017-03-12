class Solution {
public:
    vector<int> maxNumber(vector<int>& A, vector<int>& B, int K) {
        int n = A.size(), m = B.size();
        
        vector<int> ret(K, 0);
        for (int i = 0; i <= K; i++) {
            if (i <= n && K-i <= m) {
                vector<int> comb = merge(pick(A, i), pick(B, K-i), K);
                ret = max(ret, comb);
            }
        }
        return ret;
    }
    vector<int> pick(vector<int> &A, int K) {
        int idx = 0, n = A.size();
        vector<int> ret(n, 0);
        for (int i = 0; i < n; i++) {
            while (idx + (n-i) > K && idx && ret[idx-1] < A[i])
                idx--;
            ret[idx++] = A[i];
        }
        ret.resize(K);
        return ret;
    }
    vector<int> merge(vector<int> A, vector<int> B, int K) {
        vector<int> ret(K);
        int idx1 = 0, idx2 = 0, top = 0;
        int n = A.size(), m = B.size();
        while (idx1 < n || idx2 < m) {
            int flag = 0;
            for (int i = 0; idx1+i < n && idx2+i < m && flag == 0; i++) {
                if (A[idx1+i] > B[idx2+i])
                    flag = -1;
                if (A[idx1+i] < B[idx2+i])
                    flag = 1;
            }
            if (flag == 0)
                flag = n - idx1 > m - idx2 ? -1 : 1;
            if (flag == -1)
                ret[top] = A[idx1], idx1++, top++;
            else
                ret[top] = B[idx2], idx2++, top++;
        }
        return ret;
    }
};
