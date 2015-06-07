#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& A) {
        if (A.size() == 0)
            return 0;
        int ret = A[0], sum = 0;
        for (int i = 0; i < A.size(); i++) {
            if (sum > 0)    sum += A[i];
            else            sum = A[i];
            ret = max(ret, sum);
        }
        return ret;
    }
};

int main() {
    Solution s;
    int A[] = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> v(A, A+9);
    printf("%d\n", s.maxSubArray(v));
    return 0;
}