#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    double x, y;
};
#define eps 1e-8
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int inPolygon(Pt p[], Pt q, int n) {
    if(n == 1)  return 0; // false
    if(n == 2) { // on segment
        if(p[0].x > q.x != p[1].x > q.x &&
           p[0].y > q.y != p[1].y > q.y &&
           fabs(cross(p[0], p[1], q)) < eps)
           return 1;
        return 0;
    }
    int i, j, k = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
           k++;
    }
    return k&1;
}
bool cmp(Pt a, Pt b) {
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}
int monotone(Pt p[], int n, Pt ch[]) {
    sort(p, p+n, cmp);
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
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs)*cross(as, at, bt) < 0 &&
       cross(at, as, bs)*cross(at, as, bt) < 0 &&
       cross(bs, bt, as)*cross(bs, bt, at) < 0 &&
       cross(bt, bs, as)*cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
int M, C, i, j, k, l;
Pt Mp[505], Cp[505], Mch[1005], Cch[1005];
void sol() {
    int Mn = monotone(Mp, M, Mch);
    int Cn = monotone(Cp, C, Cch);
    for(i = 0; i < Cn; i++) {
        if(inPolygon(Mch, Cch[i], Mn)) {
            puts("No");
            return;
        }
    }
    for(i = 0; i < Mn; i++) {
        if(inPolygon(Cch, Mch[i], Cn)) {
            puts("No");
            return;
        }
    }
    for(i = 0, j = Mn-1; i < Mn; j = i++) {
        for(k = 0, l = Cn-1; k < Cn; l = k++) {
            if(intersection(Mch[i], Mch[j], Cch[k], Cch[l])) {
                puts("No");
                return;
            }
        }
    }
    puts("Yes");
}
int main() {
    while(scanf("%d %d", &M, &C) == 2 && M) {
        for(i = 0; i < M; i++)
            scanf("%lf %lf", &Mp[i].x, &Mp[i].y);
        for(i = 0; i < C; i++)
            scanf("%lf %lf", &Cp[i].x, &Cp[i].y);
        sol();
    }
    return 0;
}
