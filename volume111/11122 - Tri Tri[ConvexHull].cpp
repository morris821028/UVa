#include <stdio.h>
#include <algorithm>
#include <math.h>
#define eps 1e-8
using namespace std;
struct Pt {
    double x, y;
    bool operator<(const Pt &a) const {
        if(a.x != x)
            return x < a.x;
        return y < a.y;
    }
};
struct Seg {
    Pt s, e;
};
int inInterval(Seg a, Pt p) {
    return min(a.s.x, a.e.x) <= p.x &&
        p.x <= max(a.s.x, a.e.x) &&
        min(a.s.y, a.e.y) <= p.y &&
        p.y <= max(a.s.y, a.e.y);
}
int onLine(Seg a, Pt p) {
    if(fabs((a.s.x-a.e.x)*(p.y-a.s.y)-
            (a.s.y-a.e.y)*(p.x-a.s.x)) > eps)
        return 0;
    return inInterval(a, p);
}
int calcIntersection(Seg a, Seg b, Pt &p) {
    double a1, b1, c1, a2, b2, c2;
    double D, Dx, Dy;
    a1 = a.s.y-a.e.y, b1 = -a.s.x+a.e.x;
    a2 = b.s.y-b.e.y, b2 = -b.s.x+b.e.x;
    c1 = a1*a.s.x + b1*a.s.y;
    c2 = a2*b.s.x + b2*b.s.y;
    D = a1*b2 - a2*b1;
    Dx = c1*b2 - c2*b1;
    Dy = a1*c2 - a2*c1;
    if(fabs(D) < eps) // NONE or LINE
        return 0;
    p.x = Dx/D, p.y = Dy/D;
    /*printf("%lf %lf - %lf %lf\n", a.s.x, a.s.y, a.e.x, a.e.y);
    printf("%lf %lf - %lf %lf\n", b.s.x, b.s.y, b.e.x, b.e.y);
    printf("%lf %lf\n", p.x, p.y);*/
    return inInterval(a, p) && inInterval(b, p);
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int convexHull(Pt p[], int n, Pt ch[]) {
    sort(p, p+n);
    int m = 0, i, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
double calcArea(Pt p[], int n) {
    if(n < 3)   return 0;
    p[n] = p[0];
    int i;
    double area = 0;
    for(i = 0; i < n; i++)
        area += p[i].x*p[i+1].y-p[i].y*p[i+1].x;
    return fabs(area/2);
}
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}
int main() {
    int t;
    int i, j, k, l;
    int cases = 0;
    Pt A[10], B[10];
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 3; i++)
            scanf("%lf %lf", &A[i].x, &A[i].y);
        for(i = 0; i < 3; i++)
            scanf("%lf %lf", &B[i].x, &B[i].y);
        Pt P[50], CH[50], p;
        Seg a, b, c;
        int cnt = 0;
        for(i = 0; i < 3; i++) {
            if(inPolygon(B, 3, A[i]))
                P[cnt++] = A[i];
            if(inPolygon(A, 3, B[i]))
                P[cnt++] = B[i];
            for(j = 0, k = 2; j < 3; k = j++) {
                a.s = A[j], a.e = A[k];
                b.s = B[j], b.e = B[k];
                if(onLine(b, A[i]))
                    P[cnt++] = A[i];
                if(onLine(a, B[i]))
                    P[cnt++] = B[i];
            }
        }
        for(i = 0, j = 2; i < 3; j = i++) {
            for(k = 0, l = 2; k < 3; l = k++) {
                a.s = A[i], a.e = A[j];
                b.s = B[k], b.e = B[l];
                if(calcIntersection(a, b, p)) {
                    P[cnt++] = p;
                }
            }
        }
        /*for(i = 0; i < cnt; i++) {
            printf("(%.3lf, %.3lf)", P[i].x, P[i].y);
        }
        puts("");*/
        int n = convexHull(P, cnt, CH);
        double area = calcArea(CH, n);
        printf("pair %d: ", ++cases);
        if(area > eps)
            puts("yes");
        else
            puts("no");
        //printf("%lf\n", area);
    }
    return 0;
}
