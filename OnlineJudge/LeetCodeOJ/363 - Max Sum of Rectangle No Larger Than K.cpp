class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int K) {
        if (matrix.size() == 0)
            return 0;
        int flag = 0;
        int ret = INT_MIN;
        int n = matrix.size(), m = matrix[0].size();
        if (n > m)  {
            flag = 1;
            swap(n, m);
        }
        for (int i = 0; i < n; i++) {
            vector<int> sum(m, 0);
            for (int j = i; j < n; j++) {
                int prefix = 0;
                set<int> S;
                S.insert(0);
                for (int k = 0; k < m; k++) {
                    sum[k] += flag == 0 ? matrix[j][k] : matrix[k][j];
                    prefix += sum[k];
                    set<int>::iterator it = S.lower_bound(prefix - K); // find prefix - x <= K
                    if (it != S.end())
                        ret = max(ret, prefix - *it);
                    S.insert(prefix);
                }
            }
        }
        return ret;
    }
};
