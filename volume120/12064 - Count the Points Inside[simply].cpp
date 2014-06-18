#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#define eps 1e-6
using namespace std;
struct Pt {
    double x, y;
};
double dist(Pt &a, Pt &b) {
    return pow(a.x-b.x,2)+pow(a.y-b.y,2);
}
Pt circle(Pt &a, Pt &b, Pt &c) {
    static Pt ab, ac, o;
    static double a1, b1, c1, a2, b2, c2, D, D1, D2;
    ab.x = (a.x+b.x)/2, ab.y = (a.y+b.y)/2;
    ac.x = (a.x+c.x)/2, ac.y = (a.y+c.y)/2;
    a1 = a.x-b.x, b1 = a.y-b.y, c1 = a1*ab.x + b1*ab.y;
    a2 = a.x-c.x, b2 = a.y-c.y, c2 = a2*ac.x + b2*ac.y;
    D = a1*b2-a2*b1;
    D1 = c1*b2-c2*b1, D2 = a1*c2-a2*c1;
    o.x = D1/D, o.y = D2/D;
    return o;
}
Pt A, B, C, mAB;
Pt p[50000];
int main() {
    int cases = 0;
    int n, q;
    int i, j, k;
    while(scanf("%lf %lf", &A.x, &A.y) == 2) {
        scanf("%lf %lf", &B.x, &B.y);
        scanf("%d %d", &n, &q);
        if(n == 0 && q == 0)    break;
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &p[i].x, &p[i].y);
        double a, b, c; // ax + by = c
        a = A.y-B.y, b = -A.x+B.x;
        if(a < 0)   a = -a, b = -b;
        c = a*A.x + b*A.y;
        mAB.x = (A.x+B.x)/2, mAB.y = (A.y+B.y)/2;
        double na = a, nb = b;
        na /= sqrt(a*a+b*b);
        nb /= sqrt(a*a+b*b);
        if(na < 0)  na = -na, nb = -nb;
        vector<double> rSame, rDif, lSame, lDif;
        int base = 0;
        for(i = 0; i < n; i++) {
            double argv = a*p[i].x+b*p[i].y-c;
            if(fabs((A.x-B.x)*(p[i].y-A.y)-(A.y-B.y)*(p[i].x-A.x)) < eps) {
                if(min(A.x, B.x) <= p[i].x && p[i].x <= max(A.x, B.x) &&
                   min(A.y, B.y) <= p[i].y && p[i].y <= max(A.y, B.y))
                    base++;
                continue;
            }
            if(argv > 0) { // right side
                double l = 0, r = 150000, m, cr2;
                Pt C;
                int cnt = 0;
                while(l <= r && cnt < 50) {
                    m = (l+r)/2;
                    C.x = mAB.x + na*m, C.y = mAB.y + nb*m;
                    cr2 = dist(C, A);
                    if(dist(C, p[i]) <= cr2)
                        r = m;
                    else
                        l = m;
                    cnt++;
                }
                rSame.push_back(cr2);
                // circle center in left side
                l = 0, r = 150000, cnt = 0;
                while(l <= r && cnt < 50) {
                    m = (l+r)/2;
                    C.x = mAB.x - na*m, C.y = mAB.y - nb*m;
                    cr2 = dist(C, A);
                    if(dist(C, p[i]) <= cr2)
                        l = m;
                    else
                        r = m;
                    cnt++;
                }
                rDif.push_back(cr2);
            } else {// left side
                double l = 0, r = 150000, m, cr2;
                Pt C;
                int cnt = 0;
                while(l <= r && cnt < 50) {
                    m = (l+r)/2;
                    C.x = mAB.x + na*m, C.y = mAB.y + nb*m;
                    cr2 = dist(C, A);
                    if(dist(C, p[i]) <= cr2)
                        l = m;
                    else
                        r = m;
                    cnt++;
                }
                lDif.push_back(cr2);
                // circle center in left side
                l = 0, r = 150000, cnt = 0;
                while(l <= r && cnt < 50) {
                    m = (l+r)/2;
                    C.x = mAB.x - na*m, C.y = mAB.y - nb*m;
                    cr2 = dist(C, A);
                    if(dist(C, p[i]) <= cr2)
                        r = m;
                    else
                        l = m;
                    cnt++;
                }
                lSame.push_back(cr2);
            }
        }
        sort(rSame.begin(), rSame.end());
        sort(rDif.begin(), rDif.end());
        sort(lSame.begin(), lSame.end());
        sort(lDif.begin(), lDif.end());
        printf("Case %d:\n", ++cases);
        while(q--) {
            int Idx;
            scanf("%d", &Idx);
            C = p[Idx-1];
            if(fabs((A.x-B.x)*(C.y-A.y)-(A.y-B.y)*(C.x-A.x)) < eps) {
                puts("Impossible");
                continue;
            }
            C = circle(A, B, C);
            double argv = a*C.x + b*C.y - c, cr2;
            cr2 = dist(C, A);
            if(cr2 > (100000-eps)*(100000.0-eps)) {
                puts("Impossible");
                continue;
            }
            int v1, v2;
#define eps2 1e-3
            if(argv > 0) { // center in right side
                v1 = upper_bound(rSame.begin(), rSame.end(), cr2+eps2) - rSame.begin();
                v2 = upper_bound(lDif.begin(), lDif.end(), cr2-eps2) - lDif.begin();
                v2 = lDif.size()-v2;
            } else { // center in left side
                v1 = upper_bound(lSame.begin(), lSame.end(), cr2+eps2) - lSame.begin();
                v2 = upper_bound(rDif.begin(), rDif.end(), cr2-eps2) - rDif.begin();
                v2 = rDif.size()-v2;
            }
            printf("%d\n", v1+v2+2+base);
        }
    }
    return 0;
}
