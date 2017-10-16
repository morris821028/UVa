class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        int r = (B.length() + A.length()-1)/ A.length();
        string tA = "";
        for (int i = 0; i < r; i++)   
            tA += A;
        
        for (int i = 0; i < 2; i++) {
            if (tA.find(B) != string::npos)
                return r+i;
            tA += A;
        }
        return -1;
    }
};
