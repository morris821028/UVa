class Solution {
public:
    int compareVersion(string v1, string v2) {
        for (int i = 0; i < v1.length(); i++)
            if (v1[i] == '.')
                v1[i] = ' ';
        for (int i = 0; i < v2.length(); i++)
            if (v2[i] == '.')
                v2[i] = ' ';
        stringstream s1(v1), s2(v2);
        vector<int> t1, t2;
        int x;
        while (s1 >> x)
            t1.push_back(x);
        while (s2 >> x)
            t2.push_back(x);
        for (int i = 0; i < t1. size() || i < t2.size(); i++) {
            int x = i < t1.size() ? t1[i] : 0;
            int y = i < t2.size() ? t2[i] : 0;
            if (x == y)
                continue;
            if (x < y)
                return -1;
            return 1;
        }
        return 0;
    }
};
