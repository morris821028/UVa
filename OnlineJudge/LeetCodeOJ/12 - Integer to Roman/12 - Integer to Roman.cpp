class Solution {
public:
    string intToRoman(int x) {
        string rcode[13] = {"M", "CM", "D", "CD", "C", "XC", "L",
                        "XL", "X", "IX", "V", "IV", "I"};
        int val[13] = {1000, 900, 500, 400, 100, 90, 50,
                        40, 10, 9, 5, 4, 1};
        string ret = "";
    	for (int i = 0; i < 13; i++) {
	        while (x >= val[i]) {
	            x -= val[i];
	            ret += rcode[i];
	        }
	    }
	    return ret;
    }
};
