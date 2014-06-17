#include <stdio.h>
#include <math.h>

int main() {
    int t;
    double pi = 2*acos(0);
    scanf("%d", &t);
    while(t--) {
        double D, L, a, b, c;
        scanf("%lf %lf", &D, &L);
        D /= 2, L /= 2;
        c = D, a = L;
        b = sqrt(a*a-c*c);
        printf("%.3lf\n", pi*a*b);
    }
    return 0;
}
