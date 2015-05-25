#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;


class Solution {
public:
    int reverse(int x) {
        char buf[128];
        long long v = 0;
        sprintf(buf, "%d", abs(x));
        for (int i = strlen(buf)-1; i >= 0; i--)
        	v = v * 10 + buf[i] - '0';
        if (v > INT_MAX)
        	return 0;
        return x < 0 ? -v : v;
    }
};

int main() {
	Solution s;
	printf("%d", s.reverse(1000000003));
	return 0;
}
