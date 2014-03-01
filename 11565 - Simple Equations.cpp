#include <stdio.h>
#include <stdlib.h>
int A, B, C;
void sol() {
    int x, y, z, k, tB;
    if(B == 0)
        tB = A;
    else
        tB = B;
    for(x = -tB; x <= tB; x++) {
        if(x && B%x)
            continue;
        for(y = x+1; y <= tB; y++) {
            if(y && B%y)
                continue;
            z = A-x-y;
            if(y >= z)   continue;
            if(x+y+z == A && x*x+y*y+z*z == C && x*y*z == B) {
                printf("%d %d %d\n", x, y, z);
                return;
            }
        }
    }
    puts("No solution.");
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &A, &B, &C);
        sol();
    }
    return 0;
}
