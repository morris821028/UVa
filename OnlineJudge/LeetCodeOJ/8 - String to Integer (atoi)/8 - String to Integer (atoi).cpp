#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <sstream>
using namespace std;


class Solution {
public:
	
    int myAtoi(string str) {
        stringstream sin(str);
        
		if (!(sin >> str))
			return 0;
        
        int sign = 1, digit = 1;
        if (str[0] == '-')
        	sign = -1, str = str.substr(1);
        else if (str[0] == '+')
        	sign = +1, str = str.substr(1);
        	
        string numstr = "";
        for (int i = 0; i < str.length(); i++) {
        	if (isdigit(str[i]))
        		numstr += str[i];
        	else
        		break;
        }
        	
        if (numstr.length() < 1)
        	return 0;
        	
        if (numstr.length() > 10)
        	return sign > 0 ? INT_MAX : INT_MIN;
        	
        long long num = 0;
        sscanf(numstr.c_str(), "%lld", &num);
        num = num * sign;
        return (int) max(min(num, (long long) INT_MAX), (long long) INT_MIN);
    }
};

int main() {
	Solution s;
	printf("%d", s.myAtoi(" -0012a42"));
	return 0;
}
