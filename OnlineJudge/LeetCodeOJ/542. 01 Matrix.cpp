class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& A) {
        queue<int> X, Y, D;
        int n = A.size(), m = A[0].size();
        vector<vector<int>> ret(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (A[i][j] == 0)
                    X.push(i), Y.push(j), D.push(0);
            }
        }
        
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        while (!X.empty()) {
            int x = X.front();
            int y = Y.front();
            int d = D.front();
            X.pop(), Y.pop(), D.pop();
            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i], ty = y + dy[i];
                if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if (A[tx][ty] == 1 && ret[tx][ty] == 0) {
                    ret[tx][ty] = d+1;
                    X.push(tx), Y.push(ty), D.push(d+1);
                }
            }
        }
        return ret;
    }
};
