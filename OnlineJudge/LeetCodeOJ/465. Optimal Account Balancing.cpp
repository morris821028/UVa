class Solution {
public:
    int minTransfers(vector<vector<int>>& trans) {
        map<int, int> R;
        for (auto e : trans) {
            R[e[0]] -= e[2];
            R[e[1]] += e[2];
        }
        
        multiset<int> S1, S2;
        for (auto e : R) {
            if (e.second > 0)
                S1.insert(e.second);
            if (e.second < 0)
                S2.insert(-e.second);
        }
        int ret = 0;
        while (!S1.empty() && !S2.empty()) {
            int a = *S1.rbegin();
            int b = *S2.rbegin();
            int t = min(a, b);
            int ta = a - t, tb = b - t;
            S1.erase(S1.find(a));
            S2.erase(S2.find(b));
            if (ta)
                S1.insert(ta);
            if (tb)
                S2.insert(tb);
            ret++;
        }
        return ret;
    }
};
