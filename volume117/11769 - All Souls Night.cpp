#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
using namespace std;

#define eps 1e-6
const double pi = acos(-1);
struct Point3D {
    double x, y, z;
};
struct Plane3D {
    double a, b, c, d;//ax+by+cz+d = 0
    void format(Point3D f, Point3D p) {
        a = f.x, b = f.y, c = f.z;
        d = -(a*p.x + b*p.y + c*p.z);
    }
};
Point3D cross3D(Point3D o, Point3D a, Point3D b) {
    Point3D z, p, q;
    p.x = a.x-o.x, p.y = a.y-o.y, p.z = a.z-o.z;
    q.x = b.x-o.x, q.y = b.y-o.y, q.z = b.z-o.z;
    z.x = p.y*q.z - q.y*p.z;
    z.y = p.z*q.x - q.z*p.x;
    z.z = p.x*q.y - q.x*p.y;
    return z;
}
double len(Point3D p) {
    return pow(p.x,2)+pow(p.y,2)+pow(p.z,2);
}
double convex3D(Point3D p[], int n) {
    int i, j, k;
    Plane3D e;
    double ret = 0;
    for(i = 0; i < n; i++) {//A
        for(j = i+1; j < n; j++) {//B
            for(k = j+1; k < n; k++) {//C
                Point3D f = cross3D(p[i], p[j], p[k]), ff;
                if(len(f) < eps) // A-B-C inline
                    continue;
                e.format(f, p[i]);
                int neg = 0, pos = 0, no = 0, m = 0;
                for(int l = 0; l < n && !no; l++) {
                    double v = e.a*p[l].x + e.b*p[l].y + e.c*p[l].z + e.d;
                    if(fabs(v) < eps)
                        continue;
                    if(v > 0)   pos = 1;
                    else        neg = 1;
                    if(pos && neg)  no = 1;
                }
                if(no)  continue;
                double area = sqrt(len(f)), A, B, C;
                for(int l = 0; l < n && !no; l++) {
                    if(l == i || l == j || l == k)
                        continue;
                    double v = e.a*p[l].x + e.b*p[l].y + e.c*p[l].z + e.d;
                    if(fabs(v) > eps)
                        continue;
                    ff = cross3D(p[i], p[j], p[l]);
                    A = sqrt(len(ff));
                    ff = cross3D(p[i], p[l], p[k]);
                    B = sqrt(len(ff));
                    ff = cross3D(p[l], p[j], p[k]);
                    C = sqrt(len(ff));
                    if(fabs(area-A-B-C) > eps)
                        no = 1;
                }
                if(no)  continue;
                ret += area/2;
            }
        }
    }
    return ret;
}
int main() {
    int n, cases = 0;
    int i, j, k;
    Point3D p[50];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
        printf("Case %d: %.2lf\n", ++cases, convex3D(p, n));
    }
    return 0;
}
/*
4
0 0 0
4 0 0
0 4 0
0 0 4
8
0 0 0
0 0 1
0 1 0
0 1 1
1 0 0
1 0 1
1 1 0
1 1 1
*/
