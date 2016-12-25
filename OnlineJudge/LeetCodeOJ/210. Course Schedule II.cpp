class Solution {
public:
    vector<int> findOrder(int n, vector<pair<int, int>>& prerequisites) {
        vector< vector<int> > g(n, vector<int>(0));
        vector<int> indeg(n, 0);
        for (auto e : prerequisites) {
            g[e.second].push_back(e.first);
            indeg[e.first]++;
        }
        vector<int> ret;
        queue<int> Q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0)
                Q.push(i);
        }
        while (!Q.empty()) {
            int u = Q.front();
            ret.push_back(u);
            Q.pop();
            for (auto adj : g[u]) {
                if (--indeg[adj] == 0)
                    Q.push(adj);
            }
        }
        return ret.size() == n ? ret : vector<int>();
    }
};
