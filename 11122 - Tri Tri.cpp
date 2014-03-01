#include <stdio.h>
#include <math.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define eps 1e-8
struct Pt {
    double x, y;
};
struct Seg {
    Pt s, t;
};
int in(double a, double b, double c) {
    return c >= a && c <= b;
}
int onLine(Seg& a, Pt& c) {
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
double cross(Pt &o, Pt &a, Pt &b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int intersection(Seg& a, Seg& b) {
    /*if(onLine(a, b.s) || onLine(a, b.t) || onLine(b, a.s) || onLine(b, a.t))
        return 1; */
    if(cross(a.s, a.t, b.s)*cross(a.s, a.t, b.t) < 0 &&
       cross(a.t, a.s, b.s)*cross(a.t, a.s, b.t) < 0 &&
       cross(b.s, b.t, a.s)*cross(b.s, b.t, a.t) < 0 &&
       cross(b.t, b.s, a.s)*cross(b.t, b.s, a.t) < 0)
        return 1;
    return 0;
}
int inTri(Pt a, Pt b, Pt c, Pt p) {
    int f1, f2, f3;
    f1 = cross(a, p, b)*cross(a, p, c) < 0;
    f2 = cross(b, p, a)*cross(b, p, c) < 0;
    f3 = cross(c, p, b)*cross(c, p, a) < 0;
    return f1&f2&f3;
}
int same(Pt a, Pt b) {
    if(fabs(a.x-b.x) < eps && fabs(a.y-b.y) < eps)
        return 1;
    return 0;
}
int main() {
    int t, i, cases = 0;
    scanf("%d", &t);
    while(t--) {
        Pt A[3], B[3];
        for(i = 0; i < 3; i++)
            scanf("%lf %lf", &A[i].x, &A[i].y);
        for(i = 0; i < 3; i++)
            scanf("%lf %lf", &B[i].x, &B[i].y);
        int flag = 0;
        Seg a1, a2, a3, b1, b2, b3;

        a1.s = A[0], a1.t = A[1];
        a2.s = A[1], a2.t = A[2];
        a3.s = A[2], a3.t = A[0];

        b1.s = B[0], b1.t = B[1];
        b2.s = B[1], b2.t = B[2];
        b3.s = B[2], b3.t = B[0];

        flag |= intersection(a1, b1);
        flag |= intersection(a1, b2);
        flag |= intersection(a1, b3);

        flag |= intersection(a2, b1);
        flag |= intersection(a2, b2);
        flag |= intersection(a2, b3);

        flag |= intersection(a3, b1);
        flag |= intersection(a3, b2);
        flag |= intersection(a3, b3);

        flag |= inTri(A[0], A[1], A[2], B[0]);
        flag |= inTri(A[0], A[1], A[2], B[1]);
        flag |= inTri(A[0], A[1], A[2], B[2]);

        flag |= inTri(B[0], B[1], B[2], A[0]);
        flag |= inTri(B[0], B[1], B[2], A[1]);
        flag |= inTri(B[0], B[1], B[2], A[2]);

        int cnt = 0, i, j;
        for(i = 0; i < 3; i++)
            cnt += onLine(a1, B[i])+onLine(a2, B[i])+onLine(a3, B[i]);

        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                cnt -= same(A[i], B[j]);
            }
        }
        //printf("%d\n", cnt);
        if(cnt >= 2)    flag = 1;
        cnt = 0;
        for(i = 0; i < 3; i++)
            cnt += onLine(b1, A[i])+onLine(b2, A[i])+onLine(b3, A[i]);

        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                cnt -= same(A[i], B[j]);
            }
        }
        if(cnt >= 2)    flag = 1;
        //printf("%d\n", cnt);
        printf("pair %d: ", ++cases);
        if(flag)    puts("yes"); // 交集
        else        puts("no"); // 沒交集
    }
    return 0;
}
/*
3

0.0 0.0 1.0 0.0 0.0 2.0
0.0 0.0 -1.0 0.0 -1.0 -1.0

0.0 0.0 1.0 0.0 0.0 2.0
-0.5 -0.5 -1.0 0.0 -1.0 -1.0



*/
