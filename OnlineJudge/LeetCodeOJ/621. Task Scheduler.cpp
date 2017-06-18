class Solution {
public:
    struct cmp {
        bool operator() (pair<int, int> a, pair<int, int> b) const {
            if (a.first != b.first)
                return a.first > b.first;
            return a.second < b.second;
        }
    };
    int leastInterval(vector<char>& tasks, int n) {
        int C[128] = {};
        for (auto c: tasks)
            C[c]++;
        multiset< pair<int, int>, cmp> A;
        for (int i = 0; i < 128; i++) {
            if (C[i])
                A.insert(make_pair(C[i], 0));
        }
        
        int ret = 0;
        while (A.size()) {
            for (auto &b : A) {
                if (b.second <= ret) {
                    A.erase(A.find(b));
                    if (b.first > 1)
                        A.insert(make_pair(b.first-1, b.second+n+1));
                    break;
                }
            }
            ret++;
        }
        return ret;
    }
};
