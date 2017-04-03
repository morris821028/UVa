class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        char buf[64];
        int p, q, i, j;
        sscanf(a.c_str(), "%d+%di", &p, &q);
        sscanf(b.c_str(), "%d+%di", &i, &j);
        sprintf(buf, "%d+%di", (p*i-q*j), (p*j+q*i));
        string ret(buf);
        return ret;
    }
};
