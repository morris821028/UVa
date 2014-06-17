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
#define eps 1e-8
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
    if(A.r+B.r+eps < disAB || A.r+disAB+eps < B.r || B.r+disAB+eps < A.r) {
        if(disAB < B.r-A.r)
            return 3; //cover all special case
        return -1;
    }
    double vx, vy;
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
                return 3; // cover all special case
            } else { //((B)A)
                v[0].x = B.x+vx*B.r/(A.r-B.r);
                v[0].y = B.y+vy*B.r/(A.r-B.r);
            }
        }
        return 1;
    }
    double theta = acos((A.r*A.r+disAB*disAB-B.r*B.r)/2/A.r/disAB);
    double rvx, rvy; //rotate vector
    v[0].x = theta;
    v[1].x = vx;
    v[1].y = vy;
    /*rvx = vx*cos(theta)-vy*sin(theta);
    rvy = vx*sin(theta)+vy*cos(theta);
    v[0].x = A.x+rvx*A.r/disAB;
    v[0].y = A.y+rvy*A.r/disAB;
    rvx = vx*cos(-theta)-vy*sin(-theta);
    rvy = vx*sin(-theta)+vy*cos(-theta);
    v[1].x = A.x+rvx*A.r/disAB;
    v[1].y = A.y+rvy*A.r/disAB;*/
    return 2;
}
const double pi = acos(-1);
int main() {
    int t, n;
    int i, j, k;
    scanf("%d", &t);
    Cir D[105];
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            D[i].scan();
        double ans = 0, L, R, M, tx, ty;
        int Iidx;
        Pt Interval[205];
        Pt p[2];
        for(i = 0; i < n; i++) {
            Iidx = 0;
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                int r = IntersectCir(D[i], D[j], p);
                if(r == 3)  break;
                if(r < 2)   continue;
                double theta = p[0].x;
                double theta2 = atan2(p[1].y, p[1].x);
                /*L = atan2(p[0].y-D[i].y, p[0].x-D[i].x);
                R = atan2(p[1].y-D[i].y, p[1].x-D[i].x);*/
                L = theta2 + theta;
                R = theta2 - theta;
                if(L < -pi) L += 2*pi;
                if(L > pi)  L -= 2*pi;
                if(R < -pi) R += 2*pi;
                if(R > pi)  R -= 2*pi;
                if(L > R)
                    M = L, L = R, R = M;
                M = (L+R)/2;
                tx = D[i].x+D[i].r*cos(M);
                ty = D[i].y+D[i].r*sin(M);
                if((tx-D[j].x)*(tx-D[j].x)+(ty-D[j].y)*(ty-D[j].y) < D[j].r*D[j].r) {
                    Interval[Iidx].x = L;
                    Interval[Iidx++].y = R;
                    /*printf("%lf %lf\n", L, R);*/
                } else {
                    Interval[Iidx].x = -pi;
                    Interval[Iidx++].y = L;
                    Interval[Iidx].x = R;
                    Interval[Iidx++].y = pi;
                    /*printf("%lf %lf\n", R, pi);
                    printf("%lf %lf\n", -pi, L);*/
                }
            }
            if(j != n)  continue;
            sort(Interval, Interval+Iidx);
            double rr = -pi;
            for(j = 0; j < Iidx; j++) {
                if(Interval[j].x < rr+eps)
                    rr = max(Interval[j].y, rr);
                else {
                    ans += D[i].r*(Interval[j].x-rr);
                    rr = Interval[j].y;
                }
            }
            ans += D[i].r*(pi-rr);
        }
        double a = log10(ans), b;
        b = floor(a);
        a = a-b;
        printf("%.2lf %d\n", pow(10, a)+eps, (int)b);
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
