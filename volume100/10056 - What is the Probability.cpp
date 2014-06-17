#include <stdio.h>
#include <math.h>
int main() {
    int t, n, i;
    double p;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %lf %d", &n, &p, &i);
        if(p == 0)
            puts("0.0000");
        else
            printf("%.4lf\n", p*pow(1-p, i-1)/(1-pow(1-p, n)));
    }
    return 0;
}
