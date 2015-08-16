#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-10
struct Disk {
    double x, y, r;
    Disk(double a = 0, double b = 0, double c = 0):
    x(a), y(b), r(c) {}
    bool outside(double tx, double ty) {
        return (x - tx)*(x - tx) + (y - ty)*(y - ty) > r * r - eps;
    }
};
struct Mass {
    double x, y, m; // mass center
    Mass(double a = 0, double b = 0, double c = 0):
    x(a), y(b), m(c) {}
    Mass operator+(const Mass &a) const {
        double tx, ty, tm;
        tx = (x * m + a.x * a.m) / (m + a.m);
        ty = (y * m + a.y * a.m) / (m + a.m);
        tm = m + a.m;
        return Mass(tx, ty, tm);
    }
};
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        Disk disks[1024];
        for (int i = 0; i < n; i++) {
            double x, y, r;
            scanf("%lf %lf %lf", &x, &y, &r);
            disks[i] = Disk(x, y, r);
        }
        
        int ret = 1, errIdx = 0;
        for (int i = 0; i < n; i++) {
            Mass up(disks[i].x, disks[i].y, disks[i].r*disks[i].r);
            for (int j = i-1; j >= 0; j--) {
                if (disks[j].outside(up.x, up.y)) {
                    ret = 0, errIdx = i;
                    break;
                }
                up = up + Mass(disks[j].x, disks[j].y, disks[j].r*disks[j].r);
            }
            if (!ret)
                break;
        }
        if (ret)
            puts("Feasible");
        else
            printf("Unfeasible %d\n", errIdx);
    }
    return 0;
}
/*
 3
 0 0 10
 2 0 12
 -4 1 1
 4
 0 0 12
 0 0 10
 0 9 10
 0 17 5
 4
 0 0 4
 0 1 4
 1 0 4
 -1 -1 4
 2
 10 10 5
 0 0 3
 0
*/
