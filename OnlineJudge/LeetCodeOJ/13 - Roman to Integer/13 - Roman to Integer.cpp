#include <iostream>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        string rcode[13] = {"M", "CM", "D", "CD", "C", "XC", "L",
                                "XL", "X", "IX", "V", "IV", "I"};
        int val[13] = {1000, 900, 500, 400, 100, 90, 50,
                        40, 10, 9, 5, 4, 1};
        int ret = 0;
        for (int i = 0; i < s.length(); ) {
            for (int j = 0; j < 13; j++) {
                if (s.find(rcode[j], i) == i) {
                    i += rcode[j].length();
                    ret += val[j];
                    break;
                }
            }
        }
        return ret;
    }
};

int main() {
	Solution s;
	printf("%d\n", s.romanToInt("MMXIV"));
	return 0;
}
