#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    double x, y;
    Pt(double a, double b):
        x(a), y(b) {}
    Pt():
        x(0), y(0) {}
    Pt operator-(const Pt &a) {
        return Pt(x-a.x, y-a.y);
    }
};
Pt D[100000];
double mxdist[100000];
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
#define eps 1e-6
double dist(Pt &a, Pt &b) {
    return pow(a.x-b.x, 2) + pow(a.y-b.y, 2);
}
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &D[i].x, &D[i].y);
            mxdist[i] = 0;
            D[i+n] = D[i];
        }
        double d1, d2;
        for(i = 0; i < n; i++) {
            int l = i+1, r = n-1, mid, midmid;
            double xx = 0;
            int mnidx = i, idx;
            int cnt = 0;
            while(l < r) {
                mid = (l+r)/2, midmid = (mid+r)/2;
                d1 = dist(D[mid], D[i]);
                d2 = dist(D[midmid], D[i]);
                if(d1 > xx+eps || (fabs(d1-xx) < eps && mnidx > mid)) {
                    xx = d1;
                    mnidx = mid;
                }
                if(d2 > xx+eps || (fabs(d2-xx) < eps && mnidx > midmid)) {
                    xx = d2;
                    mnidx = midmid;
                }
                if(d1 > d2)
                    r = midmid;
                else
                    l = mid+1;
            }
            while(true) {
                idx = mnidx+1;
                if(idx >= n)     break;
                d1 = dist(D[i], D[idx]);
                if(d1 > xx+eps) {
                    xx = d1;
                    mnidx = idx;
                } else {
                    break;
                }
            }
            while(true) {
                idx = mnidx-1;
                if(idx < 0)     idx += n;
                d1 = dist(D[i], D[idx]);
                if(d1 > xx+eps || (fabs(d1-xx) < eps && mnidx > idx)) {
                    xx = d1;
                    mnidx = idx;
                }
                if(d1 < xx)
                    break;
            }

            l = n, r = i+n-1;
            cnt = 0;
            while(l < r) {
                mid = (l+r)/2, midmid = (mid+r)/2;
                d1 = dist(D[mid], D[i]);
                d2 = dist(D[midmid], D[i]);
                if(d1 > xx+eps || (fabs(d1-xx) < eps && mnidx > mid-n)) {
                    xx = d1;
                    mnidx = mid-n;
                }
                if(d2 > xx+eps || (fabs(d2-xx) < eps && mnidx > midmid-n)) {
                    xx = d2;
                    mnidx = midmid-n;
                }
                if(d1 > d2)
                    r = midmid;
                else
                    l = mid+1;
            }
            while(true) {
                idx = mnidx+1;
                if(idx >= n)     break;
                d1 = dist(D[i], D[idx]);
                if(d1 > xx+eps) {
                    xx = d1;
                    mnidx = idx;
                } else {
                    break;
                }
            }
            while(true) {
                idx = mnidx-1;
                if(idx < 0)     idx += n;
                d1 = dist(D[i], D[idx]);
                if(d1 > xx+eps || (fabs(d1-xx) < eps && mnidx > idx)) {
                    xx = d1;
                    mnidx = idx;
                }
                if(d1 < xx) break;
            }
            printf("%d\n", mnidx+1);
            xx = 0;
            for(j = 0; j < n; j++) {
                if(dist(D[i], D[j]) > xx)
                    xx = dist(D[i], D[j]), mnidx = j;
            }
            printf("*** %d\n", mnidx+1);
        }
    }
    return 0;
}
/*
5
0 0
-4 2
-2 4
2 4
4 2
3
0 0
1 0
0 10
8
3 2
2 3
-2 3
-3 2
-3 -2
-2 -3
2 -3
3 -2
*/
