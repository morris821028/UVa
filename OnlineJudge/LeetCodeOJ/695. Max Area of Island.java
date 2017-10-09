class Solution {
    static private int dfs(int x, int y, int[][] visited, int[][] g, int n, int m) {
        if (x < 0 || y < 0 || x >= n || y >= m || g[x][y] == 0 || visited[x][y] == 1)
            return 0;
        visited[x][y] = 1;
        int ret = 1;
        ret += dfs(x+1, y, visited, g, n, m);
        ret += dfs(x-1, y, visited, g, n, m);
        ret += dfs(x, y+1, visited, g, n, m);
        ret += dfs(x, y-1, visited, g, n, m);
        return ret;
    }
    public int maxAreaOfIsland(int[][] g) {
        int n = g.length, m = g[0].length;
        int[][] visited = new int[n][m];
        
        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 1 && visited[i][j] == 0) {
                    int tmp = dfs(i, j, visited, g, n, m);
                    ret = Math.max(ret, tmp);
                }
            }
        }
        return ret;
    }
}
