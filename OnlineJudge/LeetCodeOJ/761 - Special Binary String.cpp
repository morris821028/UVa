class Solution {
public:
    string makeLargestSpecial(string s) {
        int cnt = 0;
        int prev = 0;
        vector<string> sub;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '0')
                cnt--;
            else
                cnt++;

            if (cnt == 0) {
                string v = "1" + makeLargestSpecial(s.substr(prev + 1, i - prev - 1)) + "0";
                sub.push_back(v);
                prev = i + 1;
            }
        }
        
        sort(sub.begin(), sub.end());
        stringstream ss;
        for (int i = sub.size()-1; i >= 0; i--)
            ss << sub[i];
        return ss.str();
    }
};
