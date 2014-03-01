#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    while(scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        double s = (a+b+c)/2;
        double area = sqrt(s*(s-a)*(s-b)*(s-c));
        if(a == 0 || b == 0 || c == 0)
            area = 0, s = 1;
        printf("The radius of the round table is: %.3lf\n", area/s);
    }
    return 0;
}
