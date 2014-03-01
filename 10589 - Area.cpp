#include <stdio.h>

int main() {
    int n, a;
    while(scanf("%d %d", &n, &a) == 2) {
        if(n == 0 && a == 0)
            break;
        int m = 0, i;
        double x, y;
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &y);
            if(x*x+y*y <= a*a && (x-a)*(x-a)+y*y <= a*a &&
                x*x+(y-a)*(y-a) <= a*a && (x-a)*(x-a)+(y-a)*(y-a) <= a*a)
                m++;
        }
        printf("%.5lf\n", (double)m*a*a/n);
    }
    return 0;
}
