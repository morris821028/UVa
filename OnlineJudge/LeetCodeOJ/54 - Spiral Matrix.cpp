class Solution {
public:
    void dfs(vector<vector<int>>& mtx, int lx, int ly, int rx, int ry, int dir, vector<int> &ret) {
        if (lx > rx || ly > ry) return ;
        if (dir == 0) {
            for (int i = ly; i <= ry; i++)
                ret.push_back(mtx[lx][i]);
            dfs(mtx, lx+1, ly, rx, ry, 1, ret);
        } else if (dir == 1) {
            for (int i = lx; i <= rx; i++)
                ret.push_back(mtx[i][ry]);
            dfs(mtx, lx, ly, rx, ry-1, 2, ret);
        } else if (dir == 2) {
            for (int i = ry; i >= ly; i--)
                ret.push_back(mtx[rx][i]);
            dfs(mtx, lx, ly, rx-1, ry, 3, ret);
        } else {
            for (int i = rx; i >= lx; i--)
                ret.push_back(mtx[i][ly]);
            dfs(mtx, lx, ly+1, rx, ry, 0, ret);
        }
    }
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int n = matrix.size();
        if (n == 0)
            return ret;
        int m = matrix[0].size();
        dfs(matrix, 0, 0, n-1, m-1, 0, ret);
        return ret;
    }
};
