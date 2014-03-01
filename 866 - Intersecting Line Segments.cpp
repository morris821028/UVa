#include <stdio.h>
#include <math.h>
#include <algorithm>
#define eps 1e-6
using namespace std;
struct Point {
    double x, y;
};
struct Segment {
    Point s, e;
};
int onSeg(Segment a, Point b) {
    return min(a.s.x, a.e.x) <= b.x && max(a.s.x, a.e.x) >= b.x &&
    min(a.s.y, a.e.y) <= b.y && max(a.s.y, a.e.y) >= b.y;
}
Point p;
int solve(Segment a, Segment b) {
    double a1, b1, c1, a2, b2, c2;
    double D, Dx, Dy;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x;
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    D = a1*b2-a2*b1;
    Dx = c1*b2 - c2*b1;
    Dy = a1*c2 - a2*c1;
    if(!D && (Dx || Dy)) // NONE
        return 0;
    else if(!D && !Dx && !Dy) // LINE
        return 0;
    else {
        p.x = Dx/D, p.y = Dy/D;
        if(fabs(p.x-a.s.x) < eps && fabs(p.y-a.s.y) < eps)
            return 0;
        if(fabs(p.x-a.e.x) < eps && fabs(p.y-a.e.y) < eps)
            return 0;
        if(fabs(p.x-b.s.x) < eps && fabs(p.y-b.s.y) < eps)
            return 0;
        if(fabs(p.x-b.e.x) < eps && fabs(p.y-b.e.y) < eps)
            return 0;
        if(onSeg(a, p) && onSeg(b, p))
            /*printf("POINT %.2lf %.2lf\n", p.x, p.y)*/;
        else
            return 0;
    }
    return 1;
}
int main() {
    int t, n, tn, i, j;
    scanf("%d", &t);
    while(t--) {
        Segment A[100];
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf %lf", &A[i].s.x, &A[i].s.y, &A[i].e.x, &A[i].e.y);
        do {
            tn = n;
            for(i = 0; i < n; i++) {
                for(j = i+1; j < n; j++) {
                    if(solve(A[i], A[j])) {
                        A[tn] = A[i];
                        A[i].e = p, A[tn].s = p, tn++;
                        A[tn] = A[j];
                        A[j].e = p, A[tn].s = p, tn++;
                    }
                }
            }
            if(tn != n) n = tn;
            else    break;
        } while(1);
        printf("%d\n", n);
        if(t)   puts("");
    }
    return 0;
}
