#include <stdio.h>

int main() {
    double a, b;
    int cases = 0;
    while(scanf("%lf %lf", &b, &a) == 2) {
        if(a == 0 && b == 0)    break;
        printf("Case %d: ", ++cases);
        if(b == 1)
            puts(":-\\");
        else if(a/b > (a-1)/(b-1))
            puts(":-(");
        else if(a/b > (a-1)/(b-1))
            puts(":-)");
        else
            puts(":-|");
    }
    return 0;
}
