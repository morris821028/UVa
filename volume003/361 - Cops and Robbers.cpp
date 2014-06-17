#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct Pt {
    double x, y;
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
#define eps 1e-8
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int onSeg(Pt a, Pt b, Pt p) {
    if(min(a.x, b.x)-eps <= p.x && p.x <= max(a.x, b.x)+eps &&
       min(a.y, b.y)-eps <= p.y && p.y <= max(a.y, b.x)+eps &&
       fabs(cross(a, b, p)) < eps)
       return 1;
    return 0;
}
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, k = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
           k++;
        if(onSeg(p[i], p[j], q))
            return 1;
    }
    return k&1;
}
int monotone(Pt p[], int n, Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
int main() {
    int cases = 0;
    int C, R, O;
    Pt cop[205], robber[205], q;
    Pt hcop[205], hrobber[205];
    int i, j, k;
    while(scanf("%d %d %d", &C, &R, &O) == 3) {
        if(C == 0 && R == 0 && O == 0)
            break;
        for(i = 0; i < C; i++)
            scanf("%lf %lf", &cop[i].x, &cop[i].y);
        for(i = 0; i < R; i++)
            scanf("%lf %lf", &robber[i].x, &robber[i].y);
        int nC, nR;
        nC = monotone(cop, C, hcop);
        nR = monotone(robber, R, hrobber);
        printf("Data set %d:\n", ++cases);
        while(O--) {
            scanf("%lf %lf", &q.x, &q.y);
            printf("     Citizen at (%.0lf,%.0lf) is ", q.x, q.y);
            int f1 = inPolygon(hcop, nC, q);
            if(f1 && C >= 3)
                puts("safe.");
            else {
                int f2 = inPolygon(hrobber, nR, q);
                if(f2 && R >= 3)
                    puts("robbed.");
                else
                    puts("neither.");
            }
        }
        puts("");
    }
    return 0;
}
