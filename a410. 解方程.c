#include <stdio.h>

int main() {
    int a, b, c, d, e, f;
    while(scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f) == 6) {
        int dx, dy, D;
        D = a*e - b*d;
        dx = e*c - b*f;
        dy = a*f - c*d;
        if(D == 0 && dx == 0 && dy == 0)
            puts("Too many");
        else if(D == 0)
            puts("No answer");
        else
            printf("x=%.2lf\ny=%.2lf\n", (double)dx/D, (double)dy/D);
    }
    return 0;
}
