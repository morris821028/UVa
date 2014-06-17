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
    int t, n, i, j;
    Segment line[1000];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf %lf", &line[i].s.x, &line[i].s.y, &line[i].t.x, &line[i].t.y);
        int ans = 0;
        for(i = 0; i < n; i++) {
            int flag = 0;
            for(j = 0; j < n; j++) {
                if(i == j)
                    continue;
                if(intersection(line[i], line[j])) {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
