#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#define eps 1e-5
using namespace std;
struct Pt {
    double x, y;
    bool operator<(const Pt &a) const {
        if(a.x != x)
            return x < a.x;
        return y < a.y;
    }
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
Pt p[50000], op[50000];
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("nn.txt", "w+t", stdout);
    int cases = 0;
    int n, q;
    int i, j, k;
    while(scanf("%lf %lf", &A.x, &A.y) == 2) {
        scanf("%lf %lf", &B.x, &B.y);
        scanf("%d %d", &n, &q);
        if(n == 0 && q == 0)    break;
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
            op[i] = p[i];
        }
        sort(p, p+n);
        printf("Case %d:\n", ++cases);
        double cr2;
        while(q--) {
            int Idx;
            scanf("%d", &Idx);
            C = op[Idx-1];
            if(fabs((A.x-B.x)*(C.y-A.y)-(A.y-B.y)*(C.x-A.x)) < eps) {
                puts("Impossible");
                continue;
            }
            C = circle(A, B, C);
            cr2 = dist(C, A);
            //printf("%lf\n", cr2);
            if(cr2 > 100000.0*100000.0) {
                puts("Impossible");
                continue;
            }
            double lx = C.x - sqrt(cr2);
            double rx = C.x + sqrt(cr2);
            Pt lp, rp;
            lp.x = lx-eps, lp.y = 0;
            rp.x = rx+eps, lp.y = 0;
            int l, r;
            l = lower_bound(p, p+n, lp) - p;
            r = upper_bound(p, p+n, rp) - p;
            //printf("[%lf %lf]\n", lx, rx);
            int cnt = 2;
            l--, r++;
            //printf("%lf %lf\n", C.x, C.y);
            for(i = 0; i < n; i++) {
                if(dist(C, p[i]) <= cr2+eps) {
                    //printf("%d\n", i);
                    cnt++;
                }
                //printf("%lf %lf\n", p[i].x, p[i].y);
            }
            printf("%d\n", cnt);
        }
    }
    return 0;
}
/*
0 10 10 0 6 2
-1 -1
-1 -1
3 3
5 5
-1 -1
12 16
4
1
0 10 10 0 8 2
-1 -1
2 2
4 4
6 6
8 8
12 12
14 14
16 16
3
5
0 10 10 0 0 0
Case 1:
Impossible
7
Case 2:
8
7
*/
