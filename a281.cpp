#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int Y, P;
    int S, H, I, K;
    int A, B, C, D, E;
    int i, j, k;
    while(scanf("%d %d", &Y, &P) == 2) {
        double CP = -1;
        int resS = 0;
        while(P--) {
            scanf("%d %d %d %d", &S, &H, &I, &K);
            double avgL = 0, COST, totCOST = 0, tmpCP;
            int W = 0xffff;
            for(i = 0; i < I; i++) {
                scanf("%d %d %d %d %d", &A, &B, &C, &D, &E);
                double L = C*B;
                avgL += L;
                W = min(W, D/E);
                totCOST += A;
            }
            COST = totCOST/W;
            tmpCP = avgL/COST;
            if(tmpCP > CP) {
                CP = tmpCP, resS = S;
            }
        }
        printf("%d\n", Y-resS);
    }
    return 0;
}
