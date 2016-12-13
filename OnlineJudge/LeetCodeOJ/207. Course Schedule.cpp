class Solution {
public:
    bool dfs(int u, map<int, vector<int> > &g, map<int, int> &visited, map<int, int> &parent) {
        vector<int> &adj = g[u];
        visited[u] = 1;
        for (auto v : adj) {
            if (visited[v] == 0) {
                parent[v] = u;
                if (dfs(v, g, visited, parent))
                    return true;
            } else if (visited[v] == 1) {
                if (parent.count(v) == 0 || parent[v] != u)
                    return true;
            }
        }
        visited[u] = 2;
        return false;
    }
    bool canFinish(int n, vector<pair<int, int>>& prerequisites) {
        map< int, vector<int> > g;
        for (auto e : prerequisites)
            g[e.first].push_back(e.second);
        map<int, int> visited, parent;
        bool ret = false;
        for (int i = 0; i < n && ret == false; i++) {
            if (!visited.count(i)) {
                ret |= dfs(i, g, visited, parent);
            }
        }
        return !ret;
    }
};
