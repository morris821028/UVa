#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n, Q, x, i;
    int A[50005];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        vector<int> v(A, A+n);
        vector<int>::iterator low, up;
        scanf("%d", &Q);
        while(Q--) {
            scanf("%d", &x);
            low = lower_bound(v.begin(), v.end(), x);
            up  = upper_bound(v.begin(), v.end(), x);
            if(low-v.begin() == 0)
                printf("X ");
            else
                printf("%d ", *--low);
            if(up-v.begin() == n)
                printf("X\n");
            else
                printf("%d\n", *up);
        }
    }
    return 0;
}
