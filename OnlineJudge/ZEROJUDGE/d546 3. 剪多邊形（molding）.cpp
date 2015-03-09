#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct Pt {
    double x, y;
};
Pt P[2000], CH[2000];
double calc_area(Pt P[], int n) {
    double ans = 0;
    int i;
    for(i = 0; i < n; i++)
        ans += P[i].x*P[i+1].y - P[i].y*P[i+1].x;
    return fabs(ans)/2;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-
            (a.y-o.y)*(b.x-o.x);
}
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
int monotone(int n) {
    sort(P, P+n, cmp);
    int i, m, t;
    m = 0;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(CH[m-2], CH[m-1], P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    return m;
}
int main() {
    int n, cases = 0, i;
    double p;
    while(scanf("%d %lf", &n, &p) == 2) {
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &P[i].x, &P[i].y);
        P[n] = P[0];
        double tile = calc_area(P, n);
        int m = monotone(n);
        double cont = calc_area(CH, m-1);
        printf("%d\n", (int)ceil((cont-tile)/p));
    }
    return 0;
}
