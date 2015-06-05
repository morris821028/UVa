#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector< vector<int> > permuteUnique(vector<int>& A) {
        vector< vector<int> > ret;
        
        sort(A.begin(), A.end());
        do {
            ret.push_back(A);
        } while (next_permutation(A.begin(), A.end()));
        return ret;
    }
};

int main() {
    Solution s;
    int A[] = {2,2,3};
    vector<int> v(A, A+3);
    vector< vector<int> > ret = s.permuteUnique(v);
    for (int i = 0; i < ret.size(); i++) {
        for (int j = 0; j < ret[i].size(); j++) {
            printf("%d ", ret[i][j]);
        }
        puts("");
    }
//    int A[] = {4,1,1,3,1,1,1};
//    vector<int> v(A, A+7);
//    int A[] = {1, 1};
//    vector<int> v(A, A+2);
//    printf("%d\n", s.jump(v));
    return 0;
}