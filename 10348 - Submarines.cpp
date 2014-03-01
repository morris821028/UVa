#include <stdio.h>
struct Pt {
    double x, y;
};
struct seg {
    Pt s, e;
};
struct polygon {
    int n;
    Pt p[50];
};
int inPolygon(Pt q, polygon &p) {
    int i, j, cnt = 0;
    for(i = 0, j = p.n-1; i < p.n; j = i++) {
        if(p.p[i].y > q.y != p.p[j].y > q.y &&
           q.x < (p.p[j].x-p.p[i].x)*(q.y-p.p[i].y)/(p.p[j].y-p.p[i].y) + p.p[i].x)
           cnt++;
    }
    return cnt&1;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs)*cross(as, at, bt) < 0 &&
       cross(at, as, bs)*cross(at, as, bt) < 0 &&
       cross(bs, bt, as)*cross(bs, bt, at) < 0 &&
       cross(bt, bs, as)*cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
int main() {
    seg s[150];
    polygon poly[50];
    int n, m, i, j, k, kk;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%lf %lf %lf %lf", &s[i].s.x, &s[i].s.y,
                        &s[i].e.x, &s[i].e.y);
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            scanf("%d", &poly[i].n);
            for(j = 0; j < poly[i].n; j++)
                scanf("%lf %lf", &poly[i].p[j].x, &poly[i].p[j].y);
        }
        for(i = 0; i < n; i++) {
            int flag = 0;
            for(j = 0; j < m; j++) {
                int l, r;
                l = inPolygon(s[i].s, poly[j]);
                r = inPolygon(s[i].e, poly[j]);
                if(l != r) //Partially on land
                    flag = 1;
                if(l == 1 && r == 1) {
                    flag = 2;
                    for(k = 0, kk = poly[j].n-1; k < poly[j].n; kk = k++) {
                        if(intersection(poly[j].p[k], poly[j].p[kk], s[i].s, s[i].e))
                            flag = 1;
                    }
                }
                if(flag)    break;
                l = 0, r = 0;
                for(k = 0, kk = poly[j].n-1; k < poly[j].n; kk = k++) {
                    if(intersection(poly[j].p[k], poly[j].p[kk], s[i].s, s[i].e))
                         l = 1;
                }
                if(l)
                    flag = 1;
                if(flag)    break;
            }
            printf("Submarine %d is ", i+1);
            if(!flag)
                puts("still in water.");
            else if(flag == 1)
                puts("partially on land.");
            else
                puts("completely on land.");
        }
        break;
    }
    return 0;
}
/*
1
1 3 5 3
1
8
0 0
0 4
2 4
2 2
4 2
4 4
6 4
6 0
*/
