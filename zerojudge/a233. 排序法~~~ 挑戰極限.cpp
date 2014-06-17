#include<stdio.h>
#define    MaxN 1000001
void RadixSort(int *A, int *B, int n) {
    int i, x, d, *T, C[16];
    for(x = 0; x < 8; x++) {
        d = x*4;
        for(i = 0; i < 16; i++)        C[i] = 0;
        for(i = 0; i < n; i++)        C[(A[i]>>d)&15]++;
        for(i = 1; i < 16 ; i++)    C[i] += C[i-1];
        for(i = n-1; i >= 0; i--)    B[--C[(A[i]>>d)&15]] = A[i];
        T = A, A = B, B = T;
    }    
}
int S0[MaxN], S1[MaxN];
main() {
    int n, a;
    while(scanf("%d", &n) == 1) {
        for(a = 0; a < n; a++)	scanf("%d", &S0[a]);
        RadixSort(S0, S1, n);
        for(a = 0; a < n; a++)	printf("%d ", S0[a]);
        puts("");
    }
    return 0;
}
