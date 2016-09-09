class Solution {
public:
    int isVowel(char c) {
        switch(c) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                return 1;
        }
        return 0;
    }
    string reverseVowels(string s) {
        vector<char> c;
        for (int i = 0; i < s.length(); i++) {
            if (isVowel(s[i]))
                c.push_back(s[i]);
        }
        for (int i = 0, j = c.size()-1; i < s.length(); i++) {
            if (isVowel(s[i]))
                s[i] = c[j], j--;
        }
        return s;
    }
};
