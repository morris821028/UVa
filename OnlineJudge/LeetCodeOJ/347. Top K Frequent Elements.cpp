class Solution {
public:
    vector<int> topKFrequent(vector<int>& A, int k) {
        unordered_map<int, int> H;
        for (auto x : A) 
            H[x]++;
        
        set< pair<int, int> > S;
        for (auto e : H) {
            S.insert({e.second, e.first});
            if (S.size() > k)
                S.erase(S.begin());
        }
        
        vector<int> ret;
        for (auto e : S)
            ret.push_back(e.second);
        return ret;
    }
};
