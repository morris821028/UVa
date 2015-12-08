#include "subset.h"
 
int subset(int A[], int n, int K, int S) {
    if (S == 0 && K == 0)
        return 1;
    if (K < 0 || S < 0 || n == 0 || S > n)    
        return 0;
    return subset(A+1, n-1, K-A[0], S-1) || subset(A+1, n-1, K, S);
}
