#include <stdio.h>

int main() {
    int n;
    int D[7] = {1000,500,100,50,10,5,1};
    while(scanf("%d", &n) == 1) {
        int A[7] = {};
        int i;
        for(i = 0; i < 7; i++) {
            A[i] = n/D[i];
            n %= D[i];
        }
        int M[7] = {}, N[7] = {};
        for(i = 0; i < 7; i++) {
            if(A[i]%2) {
                M[i] = A[i]/2+1;
                N[i] = A[i]-M[i];
                for(i++; i < 7; i++)
                    N[i] = A[i];
                break;
            }
            M[i] = A[i]/2;
            N[i] = A[i]/2;
        }
        int s1 = 0, s2 = 0;
        for(i = 0; i < 7; i++) {
            if(i)   putchar(' ');
            printf("%d", M[i]);
            s1 += M[i] * D[i];
        }
        puts("");
        for(i = 0; i < 7; i++) {
            if(i)   putchar(' ');
            printf("%d", N[i]);
            s2 += N[i] * D[i];
        }
        puts("");
        printf("%d\n", s1-s2);

    }
    return 0;
}
