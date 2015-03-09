#include<stdio.h>
#include<stdlib.h>
#define MaxV 2147483647
main() {
    int U, L, a, b, c;
    int IU[1000], IL[1000];
    while(scanf("%d %d", &U, &L) == 2) {
        for(a = 0; a < U; a++)
            scanf("%d", &IU[a]);
        for(a = 0; a < L; a++)
            scanf("%d", &IL[a]);
        int Min1[1000] = {}, Min2[1000] = {}, tmin = 0;
        int *A = Min1, *B = Min2, *C;
        for(a = 0; a < U; a++) {
            for(b = a, c = L-(U-a); b <= c; b++) {
                B[b] = abs(IU[a]-IL[b]) + tmin;
                tmin = (tmin < A[b]) ? tmin : A[b];
            }
            C = A, A = B, B = C;
            tmin = A[a];
        }
        for(a = U-1, tmin = MaxV; a < L; a++)
            tmin = (tmin < A[a]) ? tmin : A[a];
        printf("%d\n", tmin);
    }
    return 0;
}
