#include <stdio.h>
#include <string.h> 
#include <iostream>
using namespace std;


class Solution {
public:
    string convert(string s, int numRows) {
        string rstr[numRows], ret = "";
        int idx = 0;
        
        for (int it = 0; idx < s.length(); it++) {
            if (it%2 == 0) {
            	for (int j = 0; j < numRows && idx < s.length(); j++)
            		rstr[j] += s[idx++];
            } else {
            	for (int j = numRows-2; j > 0 && idx < s.length(); j--)
            		rstr[j] += s[idx++];
            }
        }
        
        for (int i = 0; i < numRows; i++)
        	ret += rstr[i];
        
        return ret;
    }
};

int main() {
	Solution s;
	s.convert("PAYPALISHIRING", 3);
	s.convert("ABC", 2);
	return 0;
}
