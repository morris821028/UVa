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
    /*freopen("in.txt", "r+t", stdin);
	freopen("nlogn.txt", "w+t", stdout);*/
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
        //if(fabs(a/(a*a+b*b)) < eps && b < 0)  b = -b;
        c = a*A.x + b*A.y;
        mAB.x = (A.x+B.x)/2, mAB.y = (A.y+B.y)/2;
        //printf("%lf x + %lf y = %lf\n", a, b, c);
        double na = a, nb = b;
        na /= sqrt(a*a+b*b);
        nb /= sqrt(a*a+b*b);
        if(na < 0)  na = -na, nb = -nb;
        vector<double> rSame, rDif, lSame, lDif;
        int base = 0;
        for(i = 0; i < n; i++) {
            //printf("pt %lf %lf\n", p[i].x, p[i].y);
            double argv = a*p[i].x+b*p[i].y-c;
            if(fabs((A.x-B.x)*(p[i].y-A.y)-(A.y-B.y)*(p[i].x-A.x)) < eps) {
                if(min(A.x, B.x) <= p[i].x && p[i].x <= max(A.x, B.x) &&
                   min(A.y, B.y) <= p[i].y && p[i].y <= max(A.y, B.y))
                    base++;
                //puts("Impossible");
                continue;
            }
            if(argv > 0) { // right side
                //printf("%d\n", i);
                // circle center in right side
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
                /*printf("rDif %lf\n", cr2);
                printf("%lf %lf %lf\n", cr2, p[i].x, p[i].y);*/
                rDif.push_back(cr2);
            } else {// left side
                // circle center in right side
                //printf("%lf\n", argv);
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

                /*printf("lDif %lf\n", cr2);
                printf("%lf %lf %lf\n", cr2, p[i].x, p[i].y);*/
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
                //printf("%lf %lf %lf\n", cr2, C.x, C.y);
            }
        }
        sort(rSame.begin(), rSame.end());
        sort(rDif.begin(), rDif.end());
        sort(lSame.begin(), lSame.end());
        sort(lDif.begin(), lDif.end());
        /*for(i = 0; i < rSame.size(); i++)
            printf("%lf ", rSame[i]);
        puts(" : rSame");
        for(i = 0; i < lSame.size(); i++)
            printf("%lf ", lSame[i]);
        puts(" : lSame");
        for(i = 0; i < rDif.size(); i++)
            printf("%lf ", rDif[i]);
        puts(" : rDif");
        for(i = 0; i < lDif.size(); i++)
            printf("%lf ", lDif[i]);
        puts(" : lDif");*/
        printf("Case %d:\n", ++cases);
        while(q--) {
            int Idx;
            scanf("%d", &Idx);
            C = p[Idx-1];
            if(fabs((A.x-B.x)*(C.y-A.y)-(A.y-B.y)*(C.x-A.x)) < eps) {
                puts("Impossible");
                continue;
            }
            //printf("%lf %lf\n", C.x, C.y);
            C = circle(A, B, C);
            double argv = a*C.x + b*C.y - c, cr2;
            cr2 = dist(C, A);
            //printf("%lf %lf %lf\n", C.x, C.y, cr2);
            if(cr2 > (100000-eps)*(100000.0-eps)) {
                puts("Impossible");
                continue;
            }
            //printf("%lf %lf %lf\n", C.x, C.y, cr2);
            int v1, v2;
#define eps2 1e-3
            if(argv > 0) { // center in right side
                //puts("right side");
                v1 = upper_bound(rSame.begin(), rSame.end(), cr2+eps2) - rSame.begin();
                v2 = upper_bound(lDif.begin(), lDif.end(), cr2-eps2) - lDif.begin();
                v2 = lDif.size()-v2;
            } else { // center in left side
                //puts("left side");
                v1 = upper_bound(lSame.begin(), lSame.end(), cr2+eps2) - lSame.begin();
                v2 = upper_bound(rDif.begin(), rDif.end(), cr2-eps2) - rDif.begin();
                v2 = rDif.size()-v2;
            }
            //printf("%d %d\n", v1, v2);
            printf("%d\n", v1+v2+2+base);
        }
    }
    return 0;
}
/*
570 4502 2317 8897 78 81
6248 2485
1526 6730
5462 2645
5778 6858
9269 2526
9372 677
832 6361
2482 1834
9497 3605
219 6679
8808 4727
4696 8986
1619 8687
5176 166
2207 9212
9947 552
4645 3554
2457 586
1193 4411
4100 9991
8871 845
7883 4656
2911 395
7073 9935
3091 5182
717 715
1197 7237
6483 1243
2519 8794
8515 3550
8869 2791
7088 7450
9733 4216
532 788
6251 5411
9858 6480
6950 2566
9692 376
2103 4384
678 7746
8995 3363
3115 701
967 9144
3774 3133
2699 4835
6115 3496
2282 6824
5840 1215
8064 6398
926 5537
1461 7972
1492 9196
8618 3314
2278 1893
1665 6752
1754 5322
770 6732
923 4743
7531 7624
3233 4550
2360 8243
1873 2042
1747 8201
4801 2541
1902 2573
3343 72
3134 1350
6658 596
858 327
7649 4767
3109 84
739 7841
3848 4418
3879 6911
1331 6782
3508 6047
805 3761
9747 5501
50
*/
