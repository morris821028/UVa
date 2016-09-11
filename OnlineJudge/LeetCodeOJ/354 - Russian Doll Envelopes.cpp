class Solution {
public:
    static bool cmp(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    }
    int maxEnvelopes(vector<pair<int, int>>& e) {
        int n = e.size();
        sort(e.begin(), e.end(), cmp);
        vector<int> LIS;
        for (int i = 0; i < n; i++) {
            int v = e[i].second;
            int pos = (int) (lower_bound(LIS.begin(), LIS.end(), v) - LIS.begin());
            if (pos == LIS.size())
                LIS.push_back(v);
            else
                LIS[pos] = v;
        }
        return LIS.size();
    }
};
