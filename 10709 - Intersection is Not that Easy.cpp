#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#define eps 1e-6
using namespace std;
struct Point {
    double x, y;
};
struct LINE {
    Point s, e;
    char p[20];
};
int onSeg(LINE a, Point b) {
    return min(a.s.x, a.e.x) <= b.x && max(a.s.x, a.e.x) >= b.x &&
    min(a.s.y, a.e.y) <= b.y && max(a.s.y, a.e.y) >= b.y;
}
double dist(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
void solve(LINE a, LINE b) {
    double a1, b1, c1, a2, b2, c2;
    double D, Dx, Dy;
    Point p;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x; // ax + by = c
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    D = a1*b2-a2*b1;
    Dx = c1*b2 - c2*b1;
    Dy = a1*c2 - a2*c1;
    if(!strcmp("L", a.p) && !strcmp("LS", b.p)) {
        double l1, l2;
        l1 = fabs(a1*b.s.x+b1*b.s.y-c1)/sqrt(a1*a1+b1*b1);
        l2 = fabs(a1*b.e.x+b1*b.e.y-c1)/sqrt(a1*a1+b1*b1);
        printf("%.5lf\n", min(l1, l2));
        return ;
    }
    if(!strcmp("LS", a.p) && !strcmp("L", b.p)) {
        double l1, l2;
        l1 = fabs(a2*a.s.x+b2*a.s.y-c2)/sqrt(a2*a2+b2*b2);
        l2 = fabs(a2*a.e.x+b2*a.e.y-c2)/sqrt(a2*a2+b2*b2);
        printf("%.5lf\n", min(l1, l2));
        return ;
    }
    if(!D && (Dx || Dy)) {// Parallel
        if(!strcmp("L", a.p) && !strcmp("L", b.p)) {
            printf("%.5lf\n", fabs(a1*b.s.x+b1*b.s.y-c1)/sqrt(a1*a1+b1*b1));
            return ;
        }
    }
    else if(!D && !Dx && !Dy) {// Collinear
        if(!strcmp("L", a.p) && !strcmp("L", b.p)) {
            puts("0.00000");
        } else {
            double res = dist(a.s, b.s);
            res = min(res, dist(a.s, b.e));
            res = min(res, dist(a.e, b.s));
            res = min(res, dist(a.e, b.e));
            printf("%.5lf\n", sqrt(res));
        }
        return ;
    } else {
        if(!strcmp("L", a.p) && !strcmp("L", b.p)) {
            puts("0.00000");
            return ;
        }
        p.x = Dx/D, p.y = Dy/D;
        if(fabs(p.x-a.s.x) < eps && fabs(p.y-a.s.y) < eps) {}
        else if(fabs(p.x-a.e.x) < eps && fabs(p.y-a.e.y) < eps) {}
        else if(fabs(p.x-b.s.x) < eps && fabs(p.y-b.s.y) < eps) {}
        else if(fabs(p.x-b.e.x) < eps && fabs(p.y-b.e.y) < eps) {}
        else if(onSeg(a, p) && onSeg(b, p)) {
            puts("0.00000"); // 線段相交
            return ;
        }
    }
    // LS LS
    double res = dist(a.s, b.s), t;
    res = min(res, dist(a.s, b.e));
    res = min(res, dist(a.e, b.s));
    res = min(res, dist(a.e, b.e));
    // a.s 投影 seg b
    t = -(a2*a.s.x+b2*a.s.y-c2)/(a2*a2+b2*b2);
    p.x = a.s.x + t*a2;
    p.y = a.s.y + t*b2;
    if(onSeg(b, p))
        res = min(res, fabs(a.s.x*a2+a.s.y*b2-c2)/sqrt(a2*a2+b2*b2));
    // a.e 投影 seg b
    t = -(a2*a.e.x+b2*a.e.y-c2)/(a2*a2+b2*b2);
    p.x = a.e.x + t*a2;
    p.y = a.e.y + t*b2;
    if(onSeg(b, p))
        res = min(res, fabs(a.e.x*a2+a.e.y*b2-c2)/sqrt(a2*a2+b2*b2));
    // b.s 投影 seg a
    t = -(a1*b.s.x+b1*b.s.y-c1)/(a1*a1+b1*b1);
    p.x = b.s.x + t*a1;
    p.y = b.s.y + t*b1;
    if(onSeg(a, p))
        res = min(res, fabs(b.s.x*a1+b.s.y*b1-c1)/sqrt(a1*a1+b1*b1));
    // b.e 投影 seg a
    t = -(a1*b.e.x+b1*b.e.y-c1)/(a1*a1+b1*b1);
    p.x = b.e.x + t*a1;
    p.y = b.e.y + t*b1;
    if(onSeg(a, p))
        res = min(res, fabs(b.e.x*a1+b.e.y*b1-c1)/sqrt(a1*a1+b1*b1));
    printf("%.5lf\n", res);
}
int main() {
    int n, tn, i, j;
    LINE A, B;
    while(scanf("%lf %lf %lf %lf %s", &A.s.x, &A.s.y, &A.e.x, &A.e.y, A.p) == 5) {
        scanf("%lf %lf %lf %lf %s", &B.s.x, &B.s.y, &B.e.x, &B.e.y, B.p);
        if(!strcmp("END", A.p)) break;
        solve(A, B);
    }
    return 0;
}
