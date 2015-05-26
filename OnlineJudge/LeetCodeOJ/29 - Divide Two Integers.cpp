#include <stdio.h>
#include <limits.h>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        unsigned int a, b;
        int sign = 1;
        a = dividend < 0 ? -dividend : dividend;
        b = divisor < 0 ? -divisor : divisor;
        if (a < b)	return 0;
        if (dividend < 0)	sign = -sign;
        if (divisor < 0)	sign = -sign;
        
        unsigned int ret = 0;
        int it = 0;
        for (it = 0; b < a && b < INT_MAX; it++, b <<= 1);
        
        for (; it >= 0; it--, b >>= 1)
        	if (a >= b)
        		a -= b, ret |= 1U<<it;
        		
        if (sign > 0 && ret >= INT_MAX)
        	return INT_MAX;
        return sign < 0 ? -ret : ret;
    }
};

int main() {
	Solution s;
	printf("%d\n", s.divide(-2147483648, -1));
	printf("%d\n", s.divide(5, 2));
	printf("%d\n", s.divide(5, -2));
	printf("%d\n", s.divide(-5, 2));
	printf("%d\n", s.divide(-5, -2));
	return 0;
}
