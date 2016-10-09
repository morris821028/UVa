class Solution {
public:
    int f(long long x) {
        if (x == 1)
            return 0;
        if (x == 3)
            return 2;
        if (x % 2 == 0)
            return f(x/2) + 1;
        if (x % 4 == 3)
            return f(x+1) + 1;
        else
            return f(x-1) + 1;
    }
    int integerReplacement(int n) {
        return f(n);
    }
};
