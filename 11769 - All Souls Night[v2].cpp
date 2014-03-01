#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <map>
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
        double v = sqrt(a*a+b*b+c*c);
        a /= v, b /= v, c /= v;
        if(fabs(a) > eps) {
            if(a < 0)
                a = -a, b = -b, c = -c;
        } else if(fabs(b) > eps) {
            if(b < 0)
                a = -a, b = -b, c = -c;
        } else if(fabs(c) > eps) {
            if(c < 0)
                a = -a, b = -b, c = -c;
        }
        d = -(a*p.x + b*p.y + c*p.z);
    }
    bool operator<(const Plane3D &p) const {
        if(fabs(a-p.a) > eps)
            return a < p.a;
        if(fabs(b-p.b) > eps)
            return b < p.b;
        if(fabs(c-p.c) > eps)
            return c < p.c;
        return d < p.d;
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
double plane3DconvexHull(Point3D p[], int n, Plane3D e) {
    double rotate, theta, phi;
    double a, b, c, r;
    int i, j, k;
    Point3D base = p[0];
    a = 1, b = 1, c = sqrt(pow(e.a,2)+pow(e.b,2)+pow(e.c-1,2));
    rotate = acos((a*a+b*b-c*c)/(2*a*b));
    //(x, y, z) = (rsin(theta)cos(phi), rsin(theta)sin(phi), rcos(theta))
    // base to Spherical coordinate system
    printf("rotate %lf\n", rotate*180/pi);
    printf("%lf %lf %lf\n", p[0].x, p[0].y, p[0].z);
    for(i = 1; i < n; i++) {
        a = p[i].x - base.x;
        b = p[i].y - base.y;
        c = p[i].z - base.z;
        r = sqrt(a*a+b*b+c*c);
        theta = acos(c/r);
        phi = asin(b/(sin(theta)*r));
        printf("phi %lf theta %lf\n", phi*180/pi, theta*180/pi);
        printf("o : %lf %lf %lf\n", p[i].x, p[i].y, p[i].z);
        theta += rotate;
        p[i].x = r*sin(theta)*cos(phi) + base.x;
        p[i].y = r*sin(theta)*sin(phi) + base.y;
        p[i].z = r*cos(theta) + base.z;
        printf("r : %lf %lf %lf\n", p[i].x, p[i].y, p[i].z);
    }
    puts("---");
}
double convex3D(Point3D p[], int n) {
    int i, j, k, m = 0;
    Plane3D e;
    Point3D q[n];
    double ret = 0;
    map<Plane3D, int> exist;
    map<Plane3D, int>::iterator it;
    for(i = 0; i < n; i++) {//A
        for(j = i+1; j < n; j++) {//B
            for(k = j+1; k < n; k++) {//C
                Point3D f = cross3D(p[i], p[j], p[k]), ff;
                if(len(f) < eps) // A-B-C inline
                    continue;
                e.format(f, p[i]);
                it = exist.find(e);
                if(it == exist.end())
                    exist[e] = i;
                else {
                    continue;
                }
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
                m = 0;
                for(int l = 0; l < n && !no; l++) {
                    double v = e.a*p[l].x + e.b*p[l].y + e.c*p[l].z + e.d;
                    if(fabs(v) < eps)
                        q[m++] = p[l];
                }
                printf("base(%lf %lf %lf)\n", p[i].x, p[i].y, p[i].z);
                printf("%+lf x %+lf y %+lf z  %+lf = 0\n", e.a, e.b, e.c, e.d);
                plane3DconvexHull(q, m, e);
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
