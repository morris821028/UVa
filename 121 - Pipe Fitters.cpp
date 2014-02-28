#include <stdio.h>
#include <math.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
int skew(double a, double b) {
    if(b < 1)   return 0;
    int h, sum;
    h = 1 + (int)((b-1)/sqrt(3)*2);
    sum = (h - h/2)*(int)a + h/2*(int)(a-0.5);
    return sum;
}
int main() {
    double a, b;
    while(scanf("%lf %lf", &a, &b) == 2) {
        int grid = (int)a*(int)b;
        int skewA = max(skew(a, b), skew(b, a));
        if(skewA > grid)
            printf("%d skew\n", skewA);
        else
            printf("%d grid\n", grid);
    }
    return 0;
}
