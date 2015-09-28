#include <stdio.h>

int main() {
    int n, m;
    while (scanf("%d", &n) == 1) {
        int A[128] = {}, B[128] = {}, C[256] = {};
        for (int i = n-1; i >= 0; i--)
            scanf("%d", &A[i]);
        scanf("%d", &m);
        for (int i = m-1; i >= 0; i--)
            scanf("%d", &B[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                C[i+j] += A[i]*B[j];
        for (int i = n+m-2; i >= 0; i--)
            printf("%d%c", C[i], " \n"[i==0]);
    }
    return 0;
}