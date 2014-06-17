#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const double pi = acos(-1);
typedef struct {
    double x, y;
}Pt;
Pt P[10000], CH[10000];
double cross(Pt o, Pt a, Pt b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double Calc_Area(int m) {
    double sum = 0;
    int i;
    for(i = 0; i < m-1; i++)
        sum += (CH[i].x*CH[i+1].y - CH[i].y*CH[i+1].x);
    return fabs(sum/2);
}
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
double monotone_chain(int n) {
    sort(P, P+n, cmp);
    int m = 0, i, t;
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
    return Calc_Area(m);
}
main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        double x, y, w, h, j, k, l, sum = 0;
        m = 0;
        while(n--) {
            scanf("%lf %lf %lf %lf %lf", &x, &y, &w, &h, &j);
            j = j/180*pi;
            sum += w*h;
            l = sqrt(w*w+h*h)/2;
            k = pi - (j + atan(w/h));
            P[m].x = x - l*sin(k), P[m].y = y + l*cos(k), m++;
            P[m].x = 2*x - P[m-1].x, P[m].y = 2*y - P[m-1].y, m++;
            k = atan(h/w)*2 + pi/2 - k;
            P[m].x = x - l*cos(k), P[m].y = y + l*sin(k), m++;
            P[m].x = 2*x - P[m-1].x, P[m].y = 2*y - P[m-1].y, m++;
        }
        double area = monotone_chain(m);
        printf("%.1lf %%\n", sum*100/area);
    }
    return 0;
}
