#include <stdio.h>
#include <math.h>
#include <time.h>
#define eps 1e-8
struct Point {
    double x, y;
};
double dist(Point &a, Point &b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
Point circle(Point &a, Point &b, Point &c) {
    static Point ab, ac, o;
    static double a1, b1, c1, a2, b2, c2, D, D1, D2;
    ab.x = (a.x+b.x)/2, ab.y = (a.y+b.y)/2;
    ac.x = (a.x+c.x)/2, ac.y = (a.y+c.y)/2;
    a1 = a.x-b.x, b1 = a.y-b.y;
    c1 = a1*ab.x + b1*ab.y;
    a2 = a.x-c.x, b2 = a.y-c.y;
    c2 = a2*ac.x + b2*ac.y;
    D = a1*b2-a2*b1;
    D1 = c1*b2-c2*b1;
    D2 = a1*c2-a2*c1;
    o.x = D1/D;
    o.y = D2/D;
    return o;
}
long long cnt = 0;
double minCoverCircle(Point p[], int n) {
    Point c;
    double cr = 0.0;
    int i, j, k;
    c = p[0];
    for(i = 1; i < n; i++) {
        if(dist(p[i], c) >= cr+eps) {
            c = p[i], cr = 0;
            cnt++;
            for(j = 0; j < i; j++) {
                if(dist(p[j], c) >= cr+eps) {
                    cnt++;
                    c.x = (p[i].x+p[j].x)/2;
                    c.y = (p[i].y+p[j].y)/2;
                    cr = dist(p[i], c);
                    for(k = 0; k < j; k++) {
                        if(dist(p[k], c) >= cr+eps) {
                            cnt++;
                            c = circle(p[i], p[j], p[k]);
                            cr = dist(p[i], c);
                        }
                    }
                }
            }
        }
    }
    return sqrt(cr);
}
Point p[10005];
int main() {
    freopen("in.txt", "r+t", stdin);
    int n, i;
    double r, cr;
    clock_t st, ed;
    st = clock();
    int testcase = 0;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%lf %lf", &p[i].x, &p[i].y);
        cr = minCoverCircle(p, n);
        testcase++;
        printf("%lf\n", cr);
    }
    ed = clock();
    printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC/testcase);
    printf("%f\n", (float)cnt/testcase);
    return 0;
}
