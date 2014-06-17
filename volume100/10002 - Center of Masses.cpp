#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {
    int x, y;
};
Point P[200], CH[200];
int cmp(const void *i, const void *j) {
    Point *x, *y;
    x = (Point *)i, y = (Point *)j;
    if(x->x != y->x)
        return x->x - y->x;
    return x->y - y->y;
}
int cross(Point *o, Point *a, Point *b) {
    return (o->x - a->x)*(o->y - b->y) -
            (o->y - a->y)*(o->x - b->x);
}
void centerOfMass(int n) {
    double cx, cy, nx, ny;
    double area1 = 0, area2;
    int i;
    cx = (CH[0].x+CH[1].x+CH[2].x)/3.0;
    cy = (CH[0].y+CH[1].y+CH[2].y)/3.0;
    area1 = cross(&CH[0], &CH[1], &CH[2])/2.0;

    for(i = 3; i < n-1; i++) {
        area2 = cross(&CH[0], &CH[i-1], &CH[i])/2.0;
        nx = (CH[0].x+CH[i-1].x+CH[i].x)/3.0;
        ny = (CH[0].y+CH[i-1].y+CH[i].y)/3.0;
        cx = cx + (nx-cx)*(area2)/(area1+area2);
        cy = cy + (ny-cy)*(area2)/(area1+area2);
        area1 += area2;
    }
    printf("%.3lf %.3lf\n", cx, cy);
}
void convexHull(int n) {
    qsort(P, n, sizeof(Point), cmp);
    int m = 0, t, i;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(&CH[m-2], &CH[m-1], &P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(&CH[m-2], &CH[m-1], &P[i]) <= 0)
            m--;
        CH[m++] = P[i];
    }
    if(m >= 4)
        centerOfMass(m);
}
inline int readchar() {
    const int N = 131072;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n;
    while(ReadInt(&n)) {
        if(n < 3)
            continue;
        for(int i = 0; i < n; i++) {
            ReadInt(&P[i].x);
            ReadInt(&P[i].y);
        }
        convexHull(n);
    }
    return 0;
}
