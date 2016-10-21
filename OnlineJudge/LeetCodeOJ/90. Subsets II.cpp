class Solution {
public:
    void dfs(int idx, vector< pair<int, int> > &B, vector<int> path, vector<vector<int>> &ret) {
        if (idx == B.size()) {
            ret.push_back(path);
            return ;
        }
        dfs(idx+1, B, path, ret);
        for (int i = 0; i < B[idx].second; i++) {
            path.push_back(B[idx].first);
            dfs(idx+1, B, path, ret);
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& A) {
        int n = A.size();
        vector< pair<int, int> > B;
        vector< vector<int> > ret;
        sort(A.begin(), A.end());
        for (int i = 0; i < n; ) {
            int cnt = 0, v = A[i];
            while (i < n && A[i] == v)
                cnt++, i++;
            B.push_back(make_pair(v, cnt));
        }
        
        dfs(0, B, vector<int>(), ret);
        
        return ret;
    }
};
