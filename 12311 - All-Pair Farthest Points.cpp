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
int mnidx[100000];
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double dist(Pt &a, Pt &b) {
    return pow(a.x-b.x, 2) + pow(a.y-b.y, 2);
}
int main() {
    int n, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            scanf("%lf %lf", &D[i].x, &D[i].y);
            mxdist[i] = 0;
        }
        D[n] = D[0];
        Pt o(0,0);
        double d;
#define eps 1e-8
        for(i = 0, j = 1; i < n; i++) {
            while(cross(o, D[i+1]-D[i], D[j]-D[j-1]) <= 0) {
                d = dist(D[j], D[i]);
                if(d > mxdist[i]-eps || (fabs(d-mxdist[i]) < eps && j%n < mnidx[i])) {
                    mxdist[i] = d;
                    mnidx[i] = j%n;
                }
                d = dist(D[j-1], D[i]);
                if(d > mxdist[i]-eps || (fabs(d-mxdist[i])< eps && (j-1)%n < mnidx[i])) {
                    mxdist[i] = d;
                    mnidx[i] = (j-1)%n;
                }
                j--;
                if(j == 0)  j = n;
            }
            printf("%d\n", mnidx[i]+1);
        }
    }
    return 0;
}
