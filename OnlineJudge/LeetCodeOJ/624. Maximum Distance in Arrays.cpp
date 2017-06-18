class Solution {
public:
    int maxDistance(vector<vector<int>>& A) {
        int m = A.size();
        pair<int, int> mx[2], mn[2];
        mx[0] = mx[1] = make_pair(INT_MIN, INT_MIN);
        mn[0] = mn[1] = make_pair(INT_MAX, INT_MAX);
        for (int i = 0; i < m; i++) {
            int p = A[i][0], q = A[i][A[i].size()-1];
            if (p < mn[1].first) {
                mn[1] = make_pair(p, i);
                if (mn[1] < mn[0])
                    swap(mn[1], mn[0]);
            }
            if (q > mx[1].first) {
                mx[1] = make_pair(q, i);
                if (mx[1] > mx[0])
                    swap(mx[1], mx[0]);
            }
        }
        int ret = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (mn[i].second != mx[j].second)
                    ret = max(ret, mx[j].first - mn[i].first);
            }
        }
        return ret;
    }
};
