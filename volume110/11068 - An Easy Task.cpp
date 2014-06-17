#include <stdio.h>

int main() {
    int a, b, c, d, e, f;
    while(scanf("%d %d %d", &a, &b, &c) == 3) {
        scanf("%d %d %d", &d, &e, &f);
        if(!a && !b && !c && !d && !e && !f)
            break;
        int den = a*e - b*d;
        if(den) {
            double x1, x2;
            x1 = c*e - b*f;
            if(x1)  x1 /= den;
            x2 = a*f - c*d;
            if(x2)  x2 /= den;
            printf("The fixed point is at %.2lf %.2lf.\n", x1, x2);
        } else
            puts("No fixed point exists.");
    }
    return 0;
}
