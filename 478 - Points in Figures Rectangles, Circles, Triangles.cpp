#include <stdio.h>
#define eps 0
typedef struct {
    double x, y;
} Point;
typedef struct {
    Point a, b, c;
    double r;
    int sh;
} Shape;
Shape D[1000];
double cross(Point &o, Point &a, Point &b) {
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}
int inShape(Point &a, Point &b, Point &c, Point &t) {
    if(cross(a, b, t)*cross(a, c, t) > eps) {
        return 0;
    }
    if(cross(b, a, t)*cross(b, c, t) > eps) {
        return 0;
    }
    if(cross(c, a, t)*cross(c, b, t) > eps) {
        return 0;
    }
    return 1;
}
int main() {
    int n = 0, i;
    char s[1000];
    while(scanf("%s", s)) {
        if(s[0] == '*')
            break;
        if(s[0] == 'r') {
            scanf("%lf %lf %lf %lf %lf", &D[n].a.x, &D[n].a.y, &D[n].b.x, &D[n].b.y);
            D[n].sh = 1;
        } else if(s[0] == 'c') {
            scanf("%lf %lf %lf", &D[n].a.x, &D[n].a.y, &D[n].r);
            D[n].sh = 2;
        } else {
            scanf("%lf %lf %lf %lf %lf %lf", &D[n].a.x, &D[n].a.y, &D[n].b.x, &D[n].b.y, &D[n].c.x, &D[n].c.y);
            D[n].sh = 3;
        }
        n++;
    }
    int test = 0;
    double x, y;
    while(scanf("%lf %lf", &x, &y) == 2) {
        if(x == 9999.9 && y == 9999.9)
            break;
        test++;
        int flag = 0;
        for(i = 0; i < n; i++) {
            if(D[i].sh == 1) {
                if(D[i].a.x < x && x < D[i].b.x && D[i].a.y > y && y > D[i].b.y) {
                    printf("Point %d is contained in figure %d\n", test, i+1);
                    flag = 1;
                }
            } else if(D[i].sh == 2) {
                if((D[i].a.x-x)*(D[i].a.x-x)+(D[i].a.y-y)*(D[i].a.y-y) < D[i].r*D[i].r) {
                    printf("Point %d is contained in figure %d\n", test, i+1);
                    flag = 1;
                }
            } else {
                Point t;
                t.x = x, t.y = y;
                if(inShape(D[i].a, D[i].b, D[i].c, t)) {
                    printf("Point %d is contained in figure %d\n", test, i+1);
                    flag = 1;
                }
            }
        }
        if(!flag)
            printf("Point %d is not contained in any figure\n", test);
    }
    return 0;
}
