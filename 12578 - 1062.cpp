#include <stdio.h>
#include <math.h>

int main() {
    int t;
    double pi = acos(-1), L, area;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf", &L);
        area = (L/5)*(L/5)*pi;
        printf("%.2lf %.2lf\n", area, L*L*0.6-area);
    }
    return 0;
}
