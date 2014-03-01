#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
struct Point {
    double x, y;
};
struct Segment {
    Point s, t;
};
double in(double a, double b, double c) {
    return c >= a && c <= b;
}
int onLine(Segment a, Point c) {
    static double minx, maxx, miny, maxy;
    minx = min(a.s.x, a.t.x);
    maxx = max(a.s.x, a.t.x);
    miny = min(a.s.y, a.t.y);
    maxy = max(a.s.y, a.t.y);
    if(in(minx, maxx, c.x) != 0 && in(miny, maxy, c.y) != 0) {
        if((a.s.x-a.t.x)*(c.y-a.s.y) == (a.s.y-a.t.y)*(c.x-a.s.x)) {
            return 1;
        }
    }
    return 0;
}
double cross(Point &o, Point &a, Point &b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int intersection(Segment a, Segment b) {
    if(onLine(a, b.s) || onLine(a, b.t) || onLine(b, a.s) || onLine(b, a.t))
        return 1;
    if(cross(a.s, a.t, b.s)*cross(a.s, a.t, b.t) < 0 &&
       cross(a.t, a.s, b.s)*cross(a.t, a.s, b.t) < 0 &&
       cross(b.s, b.t, a.s)*cross(b.s, b.t, a.t) < 0 &&
       cross(b.t, b.s, a.s)*cross(b.t, b.s, a.t) < 0
       )
        return 1;
    return 0;
}
int main() {
    int t;
    Segment line, edge;
    double xl, yt, xr, yb, tmp;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %lf", &line.s.x, &line.s.y);
        scanf("%lf %lf", &line.t.x, &line.t.y);
        scanf("%lf %lf %lf %lf", &xl, &yt, &xr, &yb);
        if(xl > xr)
            tmp = xl, xl = xr, xr = tmp;
        if(yt < yb)
            tmp = yt, yt = yb, yb = tmp;
        //printf("%d %d %d %d", xl, xr, yb, yt);
        if(in(xl, xr, line.s.x) && in(yb, yt, line.s.y))
            puts("T");
        else if(in(xl, xr, line.t.x) && in(yb, yt, line.t.y))
            puts("T");
        else {
            int flag = 0;
            edge.s.x = xl, edge.s.y = yt, edge.t.x = xl, edge.t.y = yb;
            flag |= intersection(edge, line);
            edge.s.x = xr, edge.s.y = yt, edge.t.x = xr, edge.t.y = yb;
            flag |= intersection(edge, line);
            edge.s.x = xl, edge.s.y = yb, edge.t.x = xr, edge.t.y = yb;
            flag |= intersection(edge, line);
            edge.s.x = xl, edge.s.y = yt, edge.t.x = xr, edge.t.y = yt;
            flag |= intersection(edge, line);
            if(flag)
                puts("T");
            else
                puts("F");
        }
    }
    return 0;
}
/*
5
0 -18 -8 -12 -1 -1 -11 -11
*/
