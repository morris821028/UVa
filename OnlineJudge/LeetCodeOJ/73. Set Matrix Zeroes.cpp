class Solution {
public:
    void setZeroes(vector<vector<int>>& g) {
        if (g.size() == 0 || g[0].size() == 0)
            return ;
        int n = g.size(), m = g[0].size();
        int resetC0 = 0, resetR0 = 0;
        // in-place 
        for (int i = 0; i < n; i++) {
            if (g[i][0] == 0)
                resetC0 = 1;
        }
        for (int i = 0; i < m; i++) {
            if (g[0][i] == 0)
                resetR0 = 1;
        }
        // mark
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (g[i][j] == 0)
                    g[i][0] = g[0][j] = 0;
            }
        }
        //
        for (int i = 1; i < n; i++) {
            if (g[i][0] == 0) {
                for (int j = 1; j < m; j++)
                    g[i][j] = 0;
            }
        }
        for (int i = 1; i < m; i++) {
            if (g[0][i] == 0) {
                for (int j = 1; j < n; j++)
                    g[j][i] = 0;
            }
        }
        if (resetC0) {
            for (int i = 0; i < n; i++)
                g[i][0] = 0;
        }
        if (resetR0) {
            for (int i = 0; i < m; i++)
                g[0][i] = 0;
        }
    }
};
