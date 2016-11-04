class Solution {
public:
    int distance(const string &x, const string &y) {
        int diff = 0;
        for (int i = 0; i < x.length(); i++) {
            diff += x[i] != y[i];
            if (diff > 1)   return diff;
        }
        return diff;
    }
    int ladderLength(string st, string ed, unordered_set<string>& wordList) {
        if (st == ed)
            return 1;
        wordList.insert(st);
        wordList.insert(ed);
        queue<string> Q;
        queue<int> IQ;
        Q.push(st), IQ.push(1);
        while (!Q.empty()) {
            string u = Q.front();
            Q.pop();
            int dist = IQ.front();
            IQ.pop();
            for (unordered_set<string>::iterator it = wordList.begin();
                it != wordList.end(); ) {
                if (distance(*it, u) != 1) {
                    it++;
                    continue;
                }
                if (*it == ed)
                    return dist+1;
                Q.push(*it), IQ.push(dist+1);
                it = wordList.erase(it);
            }
        }
        return 0;
    }
};
