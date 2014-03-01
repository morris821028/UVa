#include <stdio.h>
#include <math.h>

double dist(double a, double b, double c, double d) {
    return (a-c)*(a-c)+(b-d)*(b-d);
}
int in(double a, double b, double c) {
    return (a >= b && a <= c) || (a <= b && a >= c);
}
int main() {
    double xm, ym;
    int n;
    while(scanf("%lf %lf", &xm, &ym) == 2) {
        scanf("%d", &n);
        double x[100], y[100];
        int i;
        for(i = 0; i <= n; i++)
            scanf("%lf %lf", x+i, y+i);
        double a, b, c, px, py, t;
        double mindist = dist(xm, ym, x[0], y[0]), ax, ay;
        double tmp;
        ax = x[0], ay = y[0];
        for(i = 0; i < n; i++) {
            a = y[i]-y[i+1], b = x[i]-x[i+1];
            b *= -1;
            c = -(a*x[i] + b*y[i]); // ax+by+c = 0
            t = (-a*xm-b*ym-c)/(a*a+b*b); //projection point (xm+t*a, ym+t*b)
            px = xm+t*a, py = ym+t*b;
            if(in(px, x[i], x[i+1]) && in(py, y[i], y[i+1])) {
                tmp = fabs(a*xm+b*ym+c)/sqrt(a*a+b*b);
                if(mindist > tmp)
                    mindist = tmp, ax = px, ay = py;
            }
            tmp = dist(xm, ym, x[i+1],y[i+1]);
            if(mindist > tmp)
                mindist = tmp, ax = x[i+1], ay = y[i+1];
        }
        printf("%.4lf\n%.4lf\n", ax, ay);
    }
    return 0;
}
