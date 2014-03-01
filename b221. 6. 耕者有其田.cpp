#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 1e-6
typedef struct {
    double x, y;
} Pt;
Pt P[500], H[500];
int cmp(const void *i, const void *j) {
    static Pt *a, *b;
    a = (Pt *)i, b = (Pt *)j;
    if(a->x != b->x)
        return a->x < b->x;
    return a->y < b->y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x - o.x)*(b.y - o.y) -
            (a.y - o.y)*(b.x - o.x);
}
double calc_area(int n, Pt P[]) {
    static int i;
    double sum = 0;
    for(i = 0; i < n-1; i++)
        sum += P[i].x*P[i+1].y - P[i].y*P[i+1].x;
    return fabs(sum/2);
}
int convex(int n) {
    qsort(P, n, sizeof(Pt), cmp);
    int i, t, m = 0;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(H[m-2], H[m-1], P[i]) <= 0)
            m--;
        H[m++] = P[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(H[m-2], H[m-1], P[i]) <= 0)
            m--;
        H[m++] = P[i];
    }
    for(i = 0; i < m; i++)  P[i] = H[i];
    return m;
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &P[i].x, &P[i].y);
        n = convex(n);
        double A = calc_area(n, P);
        double l = 0xfffffff, r = 0, m;
        double x, y;
        A = A*0.5;
        for(i = 0; i < n; i++) {
            m = P[i].y/P[i].x;
            if(m < l)   l = m;
            if(m > r)   r = m;
        }
        while(fabs(l-r) > eps) {
            m = (l+r)*0.5;
            int it = 0, idx = 0;
            Pt pp[2];
            for(i = 0; i < n-1; i++) {
                if(it == 1)
                    H[idx++] = P[i];
                if((m*P[i].x - P[i].y)*(m*P[i+1].x - P[i+1].y) <= 0) {
                    x = (P[i].x*P[i+1].y - P[i].y*P[i+1].x)/
                        (m*(P[i].x - P[i+1].x) - P[i].y + P[i+1].y);
                    y = m*x;
                    if(it < 2) {
                        if(it == 1) {
                            if(fabs(x-pp[0].x) <= eps && fabs(y-pp[0].y) <= eps)
                                continue;
                        }
                        pp[it].x = x, pp[it].y = y;
                        H[idx++] = pp[it];
                        it++;
                    }
                }
            }
            H[idx++] = pp[0];
            double sum = calc_area(idx, H);
            if(fabs(sum-A) <= eps)
                break;
            if(m*H[1].x-H[1].y <= 0) {
                /*puts("left");*/
                if(sum < A)
                    r = m;
                else
                    l = m;
            } else {
                /*puts("right");*/
                if(sum < A)
                    l = m;
                else
                    r = m;
            }
        }
        printf("%.4lf\n", m);
    }
    return 0;
}
