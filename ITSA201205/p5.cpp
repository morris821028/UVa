#include <stdio.h>
#include <math.h>
struct Point {
    double x, y;
};
Point circle(Point &a, Point &b, Point &c) {
    static Point ab, ac, o;
    static double a1, b1, c1, a2, b2, c2, D, D1, D2;
    ab.x = (a.x+b.x)/2, ab.y = (a.y+b.y)/2;
    ac.x = (a.x+c.x)/2, ac.y = (a.y+c.y)/2;
    a1 = a.x-b.x, b1 = a.y-b.y;
    c1 = a1*ab.x + b1*ab.y;
    a2 = a.x-c.x, b2 = a.y-c.y;
    c2 = a2*ac.x + b2*ac.y;
    D = a1*b2-a2*b1;
    D1 = c1*b2-c2*b1;
    D2 = a1*c2-a2*c1;
    o.x = D1/D;
    o.y = D2/D;
    return o;
}
int main() {
    Point a, b, c;
    while(scanf("%lf %lf", &a.x, &a.y) == 2) {
        scanf("%lf %lf", &b.x, &b.y);
        scanf("%lf %lf", &c.x, &c.y);
        Point o = circle(a, b, c);
        double r2 = (a.x-o.x)*(a.x-o.x)+(a.y-o.y)*(a.y-o.y);
        printf("%.3lf %.3lf %.3lf\n", o.x, o.y, sqrt(r2));
    }
    return 0;
}
