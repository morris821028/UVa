#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
	void trim(string &x) {
		int s = 0, e = x.length() - 1;
		while (s < e && isspace(x[s]))
			s++;
		while (s < e && isspace(x[e]))
			e--;
		x = x.substr(s, e - s + 1);
	}
	int readFloat(string s, int &i) {
		if (s[i] == '+' || s[i] == '-')
			i++;
		int f = 0;
		while (i < s.length() && isdigit(s[i]))
			i++, f = 1;
		if (i < s.length() && s[i] == '.') {
			i++;
			while (i < s.length() && isdigit(s[i]))
				i++, f = 1;
		}
		return f == 1;
	}
	int readInt(string s, int &i) {
		if (s[i] == '+' || s[i] == '-')
			i++;
		int f = 0;
		while (i < s.length() && isdigit(s[i]))
			i++, f = 1;
		return f == 1;
	}
    bool isNumber(string s) {
        trim(s);
        int idx = 0;
        if (!readFloat(s, idx))
        	return false;
        if (idx == s.length())
        	return true;
        if (s[idx] != 'e')
        	return false;
        idx++;
        if (!readInt(s, idx))
        	return false;
        if (idx == s.length())
        	return true;
        return false;
    }
};
int main() {
	Solution s;
	printf("%d\n", s.isNumber("0"));
	printf("%d\n", s.isNumber(" 0.1 "));
	printf("%d\n", s.isNumber("abc"));
	printf("%d\n", s.isNumber("1 a"));
	printf("%d\n", s.isNumber("2e10"));
	return 0;	
}
