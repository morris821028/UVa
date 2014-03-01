#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int A[1000];
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int mx = 0, i, j;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            if(A[i] > mx)
                mx = A[i];
        }
        sort(A, A+n);
        int m = n, x;
        long long ans = 0;
        for(i = n-1; i >= 0; i--)
            if(A[i] == mx)
                m--, ans += (int)ceil(A[i]*0.4);
        for(i = n-m, j = m-1; j >= 0; i++, j--) {
            char rank[50];
            sprintf(rank, "%.lf", (double)i*100/n);
            sscanf(rank, "%d", &x);
            if(x >= 11 && x <= 30)
                ans += (int)ceil(A[j]*0.3);
            else if(x <= 60)
                ans += (int)ceil(A[j]*0.2);
            else if(x <= 80)
                ans += (int)ceil(A[j]*0.1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
