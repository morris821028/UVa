#include <stdio.h>
#include <math.h>
struct Point {
    double x, y;
};
double cross(Point &o, Point &a, Point &b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double dist(Point &a, Point &b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main() {
    Point a, b, c;
    double R, area, pi = acos(-1);
    while(scanf("%lf %lf", &a.x, &a.y) == 2) {
        scanf("%lf %lf", &b.x, &b.y);
        scanf("%lf %lf", &c.x, &c.y);
        area = fabs(cross(a, b, c))/2;
        R = dist(a, b)*dist(b, c)*dist(c, a)/4.0/area;
        printf("%.2lf\n", 2*pi*R);
    }
    return 0;
}
