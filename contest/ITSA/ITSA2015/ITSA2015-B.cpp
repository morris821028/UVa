#include <stdio.h>
#include <vector>
using namespace std;

int main() {
    int testcase;
    int N, M, N1, F1, N2, F2;
    int X1, Y1, E1, X2, Y2, E2;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &M, &N);
        scanf("%d %d %d %d %d", &X1, &Y1, &E1, &N1, &F1);
        scanf("%d %d %d %d %d", &X2, &Y2, &E2, &N2, &F2);
        
        int has = 0;
        for (int i = 0; i <= max(F1, F2); i++) {
            if (X1 == X2 && Y1 == Y2) {
                printf("robots explode at time %d\n", i);
                has = 1;
                break;
            }
            if (i < F1) {
                if (i%(N1 + E1) < N1)
                    Y1 = (Y1 + 1)%N;
                else
                    X1 = (X1 + 1)%M;
            }
            if (i < F2) {
                if (i%(N2 + E2) < E2)
                    X2 = (X2 + 1)%M;
                else
                    Y2 = (Y2 + 1)%N;
            }
        }
        
        if (!has)
            puts("robots will not explode");
    }
    return 0;
}