class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> r;
        int ret = 0, n = 0;
        for (auto e : ops) {
            if (e == "+") {
                int pt = r[n-1] + r[n-2];
                r.push_back(pt), n++;
                ret += pt;
            } else if (e == "D") {
                int pt = r[n-1]*2;
                r.push_back(pt), n++;
                ret += pt;
            } else if (e == "C") {
                int pt = r[n-1];
                ret -= pt;
                r.pop_back(), n--;
            } else {
                stringstream sin(e);
                int pt;
                sin >> pt;
                ret += pt;
                r.push_back(pt), n++;
            }
        }
        return ret;
    }
};
