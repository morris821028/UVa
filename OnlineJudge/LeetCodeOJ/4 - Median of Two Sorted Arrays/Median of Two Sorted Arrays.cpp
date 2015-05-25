#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int an = (int) A.size();
        int bn = (int) B.size();
        if ((an + bn)%2)
            return k_th_element(&A[0], an, &B[0], bn, (an+bn+1)/2);
        else
            return (k_th_element(&A[0], an, &B[0], bn, (an+bn)/2) +
                    k_th_element(&A[0], an, &B[0], bn, (an+bn)/2+1))/2.0;
    }
    int k_th_element(int *A, int an, int *B, int bn, int k) { // sorted A, B, k in [1, an+bn]
        if (an == 0)    return B[k-1];
        if (bn == 0)    return A[k-1];
        if (k == 1)     return min(A[0], B[0]);
        
        if (an/2+1 + bn/2+1 > k) {
            if (A[an/2] > B[bn/2])
                return k_th_element(A, an/2, B, bn, k);
            else
                return k_th_element(A, an, B, bn/2, k);
        } else {
            if (A[an/2] < B[bn/2])
                return k_th_element(A+an/2+1, an-(an/2+1), B, bn, k-(an/2+1));
            else
                return k_th_element(A, an, B+bn/2+1, bn-(bn/2+1), k-(bn/2+1));
        }
        return 0;
    }
};

void test() {
    Solution tool;
    for (int i = 0; i < 20; i++) {
        int n = rand()%20, m = rand()%20;
        vector<int> A, B, C;
        for (int j = 0; j < n; j++)
            A.push_back(rand());
        for (int j = 0; j < m; j++)
            B.push_back(rand());
        C = A, C.insert(C.end(), B.begin(), B.end());
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        sort(C.begin(), C.end());
        double test_v = tool.findMedianSortedArrays(A, B), ev;
        if (C.size()%2)
            ev = C[C.size()/2];
        else
            ev = (C[C.size()/2] + C[C.size()/2-1])/2.0;
        printf("Case #%d: ", i+1);
        assert(test_v == ev);
        puts("pass");
    }
}
int main() {
    test();
    return 0;
}