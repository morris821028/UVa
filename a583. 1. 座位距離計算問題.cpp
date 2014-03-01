#include <stdio.h>
#include <math.h>
int main() {
    int m, x[20], y[20], i, j;
    double tmp, mn = 0xffff;
    scanf("%*d %d", &m);
    for(i = 0; i < m; i++) {
        scanf("%d %d", x+i, y+i);
        for(j = i-1; j >= 0; j--) {
            tmp = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
            if(tmp < mn)    mn = tmp;
        }
    }
    printf("%.4lf\n", mn);
    return 0;
}
