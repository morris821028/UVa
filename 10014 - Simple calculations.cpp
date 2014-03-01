#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, i;
        double a, b, c;
        scanf("%d %lf %lf", &n, &a, &b);
        for(i = 0; i < n; i++) {
            scanf("%lf", &c);
            b -= 2*(n-i)*c;
        }
        b += n*a;
        printf("%.2lf\n", b/(n+1));
        if(t)
            puts("");
    }
    return 0;
}
