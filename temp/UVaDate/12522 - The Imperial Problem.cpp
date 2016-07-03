#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

class RomanNumber {
public:
	static string rcode[13];
	static int val[13];
    string toRoman(int x) {
    	string ret = "";
    	for (int i = 0; i < 13; i++) {
	        while (x >= val[i]) {
	            x -= val[i];
	            ret += rcode[i];
	        }
	    }
	    return ret;
    }
    int toNumber(string s) { // this problem
    	int x = 0;
    	for (int i = 0; i < s.length(); i++) {
    		if (s[i] == 'I')	x += 1;
    		if (s[i] == 'V')	x += 5;
    		if (s[i] == 'X')	x += 10;
    		if (s[i] == 'L')	x += 50;
    		if (s[i] == 'C')	x += 100;
    		if (s[i] == 'D')	x += 500;
    		if (s[i] == 'M')	x += 1000;
    	}
    	return x;
    }
} roman;
string RomanNumber::rcode[13] = {"M", "CM", "D", "CD", "C", "XC", "L",
                        "XL", "X", "IX", "V", "IV", "I"};
int RomanNumber::val[13] = {1000, 900, 500, 400, 100, 90, 50,
                        40, 10, 9, 5, 4, 1};
int main() {
	string S;
	while (cin >> S) {
		if (S == "*")
			return 0;
		int x = roman.toNumber(S);
		string R = roman.toRoman(x);
		
		int e = -1, c = -1;
		for (int i = 0; i <= S.length() - R.length(); i++) {
			int match = 0;
			for (int j = i, k = 0; k < R.length(); k++, j++)
				match += R[k] == S[j];
			int te = S.length() - match;
			int tc = R.length() - match;
			
			if (e == -1 || (te + tc < e + c) || (te + tc == e + c && te < e))
				e = te, c = tc;
		}
		printf("%d %d\n", e, c);
	}
}
/*
IIII
CCCII
CCCCIII
CCCCXXXX
XXXXVIIII
MMMDCCCCLXXXXVIIII
*
*/
