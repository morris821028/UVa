class Solution {
public:
    vector<int> getRow(int n) {
        vector<int> C[2];
        C[0] = vector<int>(n+1, 0);
        C[1] = vector<int>(n+1, 0);
        int p = 0, q = 1;
        
        C[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            C[q][0] = 1;
            for (int j = 1; j <= i; j++)
                C[q][j] = C[p][j] + C[p][j-1];
            p ^= 1, q ^= 1;
        }
        return C[p];
    }
};
