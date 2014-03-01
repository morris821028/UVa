#include <stdio.h>

int main() {
    long long A[50], B[50];
    while(scanf("%lld", &A[0]) == 1) {
        if(A[0] == 0)   break;
        B[0] = 1;
        int n = 1, m = 1;
        while(scanf("%lld", &A[n]) == 1 && A[n]) {
            if(A[n] == A[n-1])
                B[n-1]++;
            else
                B[n] = 1, n++;
            m++;
        }
        int up_len = 0, down_len = 0, upt = 0, downt = 0;
        int i, j, len;
        for(i = 0; i < n; i++) {
            j = i, len = B[i];
            while(j+1 < n && A[j+1] > A[j])
                len += B[j+1], j++;
            if(i != j) {
                up_len += len-1;
                upt ++;
                B[j] = 1;
                i = j-1;
                continue;
            }
            j = i, len = B[i];
            while(j+1 < n && A[j+1] < A[j])
                len += B[j+1], j++;
            if(i != j) {
                down_len += len-1;
                downt ++;
                B[j] = 1;
                i = j-1;
            }
        }
        if(upt == 0)    upt = 1;
        if(downt == 0)  downt = 1;
        printf("Nr values = %d:  %.6lf %.6lf\n", m, (double)up_len/upt, (double)down_len/downt);
    }
    return 0;
}
