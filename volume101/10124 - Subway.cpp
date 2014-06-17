#include <stdio.h>
#include <math.h>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int d, m, a, j;
    while(scanf("%d %d %d %d", &d, &m, &a, &j) == 4) {
        // a(t) = jt, v(t) = j*t*t/2, x(t) = j*t*t*t/6
        double time = 0, timecut = 0.001;
        double dist = d/2.0;
        double aa = 0, vv = 0, xx = 0, pv, pa;
        while(xx <= dist) {
            if(aa + j*timecut <= a && vv + (2*aa+j*timecut)*timecut/2.0 <= m) {
                pa = aa;
                aa += j*timecut;
                pv = vv;
                vv += (2*aa+j*timecut)*timecut/2.0;
                xx += pv*timecut + 2*pa*timecut*timecut/4 + j*timecut*timecut*timecut/4;
            } else {
                xx += vv*timecut;
            }
            time += timecut;
        }
        printf("%lf\n", time);
    }
    return 0;
}
