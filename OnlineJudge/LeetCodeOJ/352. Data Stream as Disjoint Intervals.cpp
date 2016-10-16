/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
public:
    /** Initialize your data structure here. */
    set< pair<int, int> > S;
    SummaryRanges() {
        
    }
    set<pair<int, int>>::iterator prev(set<pair<int, int>>::iterator it) {
        return it == S.begin() ? it : --it;
    }
    void addNum(int val) {
        set< pair<int, int> >::iterator jt = S.lower_bound(make_pair(val, val));
        set< pair<int, int> >::iterator it = prev(jt);
        if (it != S.end() && val >= it->first && val <= it->second)
            return ;
        if (jt != S.end() && val >= jt->first && val <= jt->second)
            return ;
        if (it != S.end() && jt != S.end() && it->second == val-1 && jt->first == val+1) {
            int l = it->first, r = jt->second;
            S.erase(it), S.erase(jt);
            S.insert(make_pair(l, r));
        } else if (it != S.end() && it->second == val-1) {
            int l = it->first;
            S.erase(it);
            S.insert(make_pair(l, val));
        } else if (jt != S.end() && jt->first == val+1) {
            int r = jt->second;
            S.erase(jt);
            S.insert(make_pair(val, r));
        } else {
            S.insert(make_pair(val, val));
        }
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> ret;
        for (auto e: S)
            ret.push_back(Interval(e.first, e.second));
        return ret;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
