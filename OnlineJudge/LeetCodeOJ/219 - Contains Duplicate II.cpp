#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& A, int k) {
        map<int, int> R;
        for (int i = 0; i < A.size(); i++) {
            if (R.count(A[i])) {
                int prev = R[A[i]];
                if (i - prev <= k)
                    return true;
            }
            R[A[i]] = i;
        }
        return false;
    }
};

int main() {
    Solution s;
    int A[] = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> v(A, A+9);
//    printf("%d\n", s.maxSubArray(v));
    return 0;
}