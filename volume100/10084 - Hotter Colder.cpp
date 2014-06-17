#include <stdio.h>
#include <math.h>
#include <string.h>
struct Pt {
    double x, y;
};
struct Polygon {
    Pt p[505];
    int n;
};
double calcArea(Polygon &p) {
    static int i;
    double sum = 0;
    p.p[p.n] = p.p[0];
    for(i = 0; i < p.n; i++)
        sum += p.p[i].x*p.p[i+1].y - p.p[i].y*p.p[i+1].x;
    return fabs(sum/2);
}
void print(Polygon &p) {
    for(int i = 0; i < p.n; i++)
        printf("%lf %lf\n", p.p[i].x, p.p[i].y);
    puts("=====");
}
int main() {
    int n, w = 10, h = 10;
    int i, j, k;
    double sx, sy, ex, ey, xi, yi;
    char cmd[50];
    Polygon A, B, C;
    A.n = 4;
    A.p[0].x = 0, A.p[0].y = 0;
    A.p[1].x = w, A.p[1].y = 0;
    A.p[2].x = w, A.p[2].y = h;
    A.p[3].x = 0, A.p[3].y = h;
    sx = 0, sy = 0;
    while(scanf("%lf %lf", &ex, &ey) == 2) {
        scanf("%s", cmd);
        // ax + by + c = 0
        double a, b, c;
#define eps 1e-8
        double m = -(sy-ey)/(sx-ex);
        a = sx-ex, b = sy-ey;
        c = -(a*((sx+ex)/2)+b*((sy+ey)/2));
        //printf("%lf x + %lf y + %lf = 0\n", a, b, c);
        A.p[A.n] = A.p[0];
        B.n = 0, C.n = 0;
        Pt intP[2];
        int point = 0;
        for(i = 0; i < A.n; i++) {
            if(point == 1) {
                if(B.n == 0 || fabs(B.p[B.n-1].x-A.p[i].x) > eps ||
                   fabs(B.p[B.n-1].y-A.p[i].y) > eps)
                B.p[B.n++] = A.p[i];
            } else {
                if(C.n == 0 || fabs(C.p[C.n-1].x-A.p[i].x) > eps ||
                   fabs(C.p[C.n-1].y-A.p[i].y) > eps)
                C.p[C.n++] = A.p[i];
            }
            //printf("(%lf %lf)-(%lf %lf)\n", A.p[i].x, A.p[i].y, A.p[i+1].x, A.p[i+1].y);
            if((a*A.p[i].x+b*A.p[i].y+c)*(a*A.p[i+1].x+b*A.p[i+1].y+c) <= eps) {
                if(point == 2)  continue;
                double ta, tb, tc;
                double tm = (A.p[i].y-A.p[i+1].y)/(A.p[i].x-A.p[i+1].x);
                if(fabs(A.p[i].x-A.p[i+1].x) < eps)
                    ta = 1, tb = 0, tc = -A.p[i].x;
                else
                    ta = tm, tb = -1, tc = -(A.p[i].x*ta+A.p[i].y*tb);
                // ax+by+c = 0, ta*x+tb*y+tc = 0
                //printf("%lf x + %lf y + %lf = 0\n", ta, tb, tc);
                double rx, ry, r;
                r = a*tb-ta*b;
                rx = (-c)*tb-(-tc)*b;
                ry = a*(-tc)-ta*(-c);
                rx = rx/r;
                ry = ry/r;
                if(fabs(r) < eps)   continue; // no intersection
                if(point == 1) {
                    if(fabs(rx-intP[0].x) < eps && fabs(ry-intP[0].y) < eps)
                        continue;
                }
                //printf("intersection %lf %lf\n", rx, ry);
                intP[point].x = rx, intP[point].y = ry;
                if(B.n == 0 || fabs(B.p[B.n-1].x-rx) > eps || fabs(B.p[B.n-1].y-ry) > eps)
                    B.p[B.n++] = intP[point];
                if(C.n == 0 || fabs(C.p[C.n-1].x-rx) > eps || fabs(C.p[C.n-1].y-ry) > eps)
                    C.p[C.n++] = intP[point];
                point++;
            }
        }
        if(point != 2) {
            printf("%.2lf\n", calcArea(A));
            sx = ex, sy = ey;
            continue;
        }
        int f1, f2;
        f1 = (a*B.p[B.n/2].x + b*B.p[B.n/2].y + c) < eps;
        if(!strcmp("Same", cmd))
            A.n = 0, B.n = 0, C.n = 0;
        else if(!strcmp("Hotter", cmd))
            xi = ex, yi = ey;
        else
            xi = sx, yi = sy;
        f2 = (a*xi + b*yi + c) < eps;
        if(f1 == f2 && point) {// same side
            //puts("B side");
            A = B;
        } else {
            //puts("C side");
            A = C;
        }
        while(fabs(A.p[A.n-1].x-A.p[0].x) < eps &&
           fabs(A.p[A.n-1].y-A.p[0].y) < eps)
            A.n--;
        //print(A);
        printf("%.2lf\n", calcArea(A));
        sx = ex, sy = ey;
    }
    return 0;
}
