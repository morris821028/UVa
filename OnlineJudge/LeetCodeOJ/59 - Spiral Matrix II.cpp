class Solution {
public:
    void dfs(vector<vector<int>>& mtx, int lx, int ly, int rx, int ry, int dir, int ret) {
        if (lx > rx || ly > ry) return ;
        if (dir == 0) {
            for (int i = ly; i <= ry; i++)
                mtx[lx][i] = ret++;
            dfs(mtx, lx+1, ly, rx, ry, 1, ret);
        } else if (dir == 1) {
            for (int i = lx; i <= rx; i++)
                mtx[i][ry] = ret++;
            dfs(mtx, lx, ly, rx, ry-1, 2, ret);
        } else if (dir == 2) {
            for (int i = ry; i >= ly; i--)
                mtx[rx][i] = ret++;
            dfs(mtx, lx, ly, rx-1, ry, 3, ret);
        } else {
            for (int i = rx; i >= lx; i--)
                mtx[i][ly] = ret++;
            dfs(mtx, lx, ly+1, rx, ry, 0, ret);
        }
    }

    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> mtx(n, vector<int>(n));
        dfs(mtx, 0, 0, n-1, n-1, 0, 1);
        return mtx;
    }
};
