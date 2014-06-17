#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
struct Point {
    double x, y;
};
struct Segment {
    Point s, t;
};
int in(double a, double b, double c) {
    return c >= a && c <= b;
}
int onLine(Segment& a, Point& c) {
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
int intersection(Segment& a, Segment& b) {
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
Segment stk[1005];
int stkin[1005];
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        int idx = 0;
        Segment T;
        for(i = 0; i < n; i++) {
            scanf("%lf %lf %lf %lf", &T.s.x, &T.s.y, &T.t.x, &T.t.y);
            for(j = 0, k = 0; j < idx; j++)
                if(!intersection(T, stk[j]))
                    stkin[k] = stkin[j], stk[k++] = stk[j];
            idx = k;
            stkin[idx] = i, stk[idx++] = T;
        }
        printf("Top sticks:");
        for(i = 0; i < idx; i++) {
            if(i)   putchar(',');
            printf(" %d", stkin[i]+1);
        }
        puts(".");
    }
    return 0;
}
