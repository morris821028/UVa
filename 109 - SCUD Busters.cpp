#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Point {
    int x, y;
};
Point P[20][200], CH[20][200], tCH[200], tP[200];
int CHm[20], Pn[20];
double A[20];
double area(Point CH[], int CHm, double &A) {
    int i;
    double sum = 0;
    for(i = 0; i < CHm-1; i++)
        sum += (CH[i].x*CH[i+1].y - CH[i].y*CH[i+1].x);
    A = sum/2;
}
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
void convexHull(int n, Point P[], Point CH[], int &CHm) {
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
    CHm = m;
}
int main() {
    int N = 0, i, n;
    while(scanf("%d", &n) == 1) {
        if(n < 0)
            break;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &P[N][i].x, &P[N][i].y);
        }
        convexHull(n, P[N], CH[N], CHm[N]);
        area(CH[N], CHm[N], A[N]);
        Pn[N] = n;
        N++;
    }
    double ans = 0, tarea;
    int x, y, used[20] = {}, m;
    Point tmp;
    while(scanf("%d %d", &tmp.x, &tmp.y) == 2) {
        for(i = 0; i < N; i++) {
            if(used[i])
                continue;
            memcpy(tP, P[i], sizeof(tP));
            tP[Pn[i]] = tmp;
            convexHull(Pn[i]+1, tP, tCH, m);
            area(tCH, m, tarea);
            if(tarea == A[i]) {
                used[i] = 1;
                ans += tarea;
            }
        }
    }
    printf("%.2lf\n", ans);
    return 0;
}
