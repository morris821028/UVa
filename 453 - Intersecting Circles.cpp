#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Cir {
    double x, y, r;
    int scan() {
        return scanf("%lf %lf %lf", &x, &y, &r) == 3;
    }
};
#define eps 1e-6
struct Pt {
    double x, y;
    bool operator<(const Pt other) const {
        if(fabs(x-other.x) < eps)
            return y < other.y;
        return x < other.x;
    }
};
int IntersectCir(Cir A, Cir B, Pt v[]) { // Pt v[] result buffer
    double disAB = sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
    if(fabs(disAB) < eps && fabs(A.r-B.r) < eps) {
        if(A.r < eps) {
            v[0].x = A.x;
            v[0].y = A.y;
            return 1;
        }
        return 0;
    }
    if(A.r+B.r+eps < disAB || A.r+disAB+eps < B.r || B.r+disAB+eps < A.r) {
        return -1;
    }
    double x, y, vx, vy;
    vx = B.x - A.x;
    vy = B.y - A.y;
    if(fabs(disAB-A.r-B.r) < eps || fabs(A.r-disAB-B.r) < eps ||
       fabs(B.r-A.r-disAB) < eps) {
        if(fabs(disAB-A.r-B.r) < eps) { // (A)(B)
            v[0].x = A.x+vx*A.r/(A.r+B.r);
            v[0].y = A.y+vy*A.r/(A.r+B.r);
        } else {
            if(A.r < B.r) { //((A)B)
                v[0].x = A.x-vx*A.r/(B.r-A.r);
                v[0].y = A.y-vy*A.r/(B.r-A.r);
            } else { //((B)A)
                v[0].x = B.x+vx*B.r/(A.r-B.r);
                v[0].y = B.y+vy*B.r/(A.r-B.r);
            }
        }
        return 1;
    }
    double theta = acos((A.r*A.r+disAB*disAB-B.r*B.r)/2/A.r/disAB);
    double rvx, rvy; //rotate vector
    rvx = vx*cos(theta)-vy*sin(theta);
    rvy = vx*sin(theta)+vy*cos(theta);
    v[0].x = A.x+rvx*A.r/disAB;
    v[0].y = A.y+rvy*A.r/disAB;
    rvx = vx*cos(-theta)-vy*sin(-theta);
    rvy = vx*sin(-theta)+vy*cos(-theta);
    v[1].x = A.x+rvx*A.r/disAB;
    v[1].y = A.y+rvy*A.r/disAB;
    return 2;
}
int main() {
    Cir A, B;
#define eps2 5.14e-5
    while(A.scan()) {
        B.scan();
        Pt p[2];
        int r = IntersectCir(A, B, p);
        if(r == 0)
            puts("THE CIRCLES ARE THE SAME");
        else if(r < 0)
            puts("NO INTERSECTION");
        else if(r == 1)
            printf("(%.3lf,%.3lf)\n", p[0].x+eps2, p[0].y+eps2);
        else {
            sort(p, p+2);
            printf("(%.3lf,%.3lf)(%.3lf,%.3lf)\n", p[0].x+eps2, p[0].y+eps2, p[1].x+eps2, p[1].y+eps2);
        }
    }
    return 0;
}
/*
2
3
0 0 2
2 0 2
1 1.732 2
*/
