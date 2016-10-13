class Solution {
public:
    int n, m;
    bool dfs(vector< vector<char> > &g, vector< vector<char> > &used, int x, int y, int idx, string &word) {
        if (idx == word.length())
            return true;
        if (x < 0 || y < 0 || x >= n || y >= m || used[x][y])
            return false;
        if (word[idx] != g[x][y])
            return false;
        used[x][y] = 1;
        if (dfs(g, used, x+1, y, idx+1, word))
            return true;
        if (dfs(g, used, x-1, y, idx+1, word))
            return true;
        if (dfs(g, used, x, y+1, idx+1, word))
            return true;
        if (dfs(g, used, x, y-1, idx+1, word))
            return true;
        used[x][y] = 0;
        return false;
    }
    bool exist(vector<vector<char>>& g, string word) {
        if (g.size() == 0 || g[0].size() == 0)
            return false;
        n = g.size(), m = g[0].size();
        vector< vector<char> > used(n, vector<char>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dfs(g, used, i, j, 0, word))
                    return true;
            }
        }
        return false;
    }
};
