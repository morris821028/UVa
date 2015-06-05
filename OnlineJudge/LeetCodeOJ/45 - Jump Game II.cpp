#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jump(vector<int>& A) {
        if (A.size() < 2)
            return 0;
        int l = 0, r = A[0], cnt = 1, n = (int) A.size();
        while (r < n-1) {
            int mxIdx = l;
            for (int i = l; i <= r; i++) {
                if (A[i] + i > A[mxIdx] + mxIdx)
                    mxIdx = i;
            }
            l = r + 1, r = A[mxIdx] + mxIdx, cnt++;
        }
        return cnt;
    }
};

int main() {
    Solution s;
//    int A[] = {2,3,1,1,4};
//    vector<int> v(A, A+5);
//    int A[] = {4,1,1,3,1,1,1};
//    vector<int> v(A, A+7);
    int A[] = {1, 1};
    vector<int> v(A, A+2);
    printf("%d\n", s.jump(v));
    return 0;
}