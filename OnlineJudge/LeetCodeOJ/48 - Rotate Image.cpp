#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void rotate(vector< vector<int> >& matrix) {
        vector< vector<int> > tmp;
        int n = (int) matrix.size();
        for (int i = 0; i < n; i++) {
            tmp.push_back(vector<int>(n, 0));
            for (int j = 0; j < n; j++) {
                tmp[i][j] = matrix[n-j-1][i];
            }
        }
        matrix = tmp;
    }
};

int main() {
    Solution s;
    int A[][2] = {{1, 2}, {3, 4}};
    vector< vector<int> > mtx;
    for (int i = 0; i < 2; i++) {
        vector<int> v(A[i], A[i]+2);
        mtx.push_back(v);
    }
    
    s.rotate(mtx);
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mtx[i][j]);
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