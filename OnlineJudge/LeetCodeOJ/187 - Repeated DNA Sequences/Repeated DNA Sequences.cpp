class Solution {
public:
    int toIndex(char c) {
        switch(c) {
            case 'A': return 0;
            case 'T': return 1;
            case 'C': return 2;
            case 'G': return 3;
        }
    }
    int toNumer(string &s, int st) {
        int v = 0;
        for (int i = 0; i < 10; i++)
            v = (v<<2) + toIndex(s[i+st]);
        return v;
    }
    string toString(int v) {
        string ret = "";
        for (int i = 0; i < 10; i++) {
            ret = ("ATCG"[v&3]) + ret;
            v >>= 2;
        }
        return ret;
    }
    vector<string> findRepeatedDnaSequences(string s) {
        map<int, int> R;
        vector<string> ret;
        for (int i = 0; i+10 <= s.length(); i++)
            R[toNumer(s, i)]++;
        for (map<int, int>::iterator it = R.begin();
            it != R.end(); it++) {
            if (it->second > 1) {
                ret.push_back(toString(it->first));
            }
        }
        return ret;
    }
};