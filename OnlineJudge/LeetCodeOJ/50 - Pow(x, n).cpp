#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        double ret = 1;
        unsigned int y = n;
        if (n < 0)  y = (unsigned int)(~n) + 1, x = 1/x;
        while (y) {
            if (y&1)
                ret = ret * x;
            y >>= 1, x = x * x;
        }
        return ret;
    }
};

int main() {
    Solution s;
    cout << s.myPow(2, -1) << endl;
    return 0;
}