#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#define maxP 100000
using namespace std;

typedef struct {
    double x, y;
} Point;
Point P[maxP], CH[maxP<<1];
int cmp(const void *i, const void *j) {
    Point *a, *b;
    a = (Point *)i, b = (Point *)j;
    if(a->y != b->y)
        return a->y - b->y > 0 ? 1 : -1;
    return a->x - b->x > 0 ? 1 : -1;
}
double cross(Point *o, Point *a, Point *b) {
    return (a->x - o->x)*(b->y - o->y) -
        (a->y - o->y)*(b->x - o->x);
}
void convexHull(int n) {
    qsort(P, n, sizeof(Point), cmp);
    int i, m = 0, t;
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
    for(i = 0; i < m; i++) {
        if(i)   printf(" ");
        printf("(%g,%g)", CH[i].x, CH[i].y);
    }
    puts("");
}
int main() {
    string line;
    double x, y;
    char ch;
    while(getline(cin, line)) {
        stringstream sin(line);
        int n = 0;
        while(sin >> ch >> x >> ch >> y >> ch) {
            P[n].x = x, P[n].y = y;
            n++;
        }
        convexHull(n);
    }
    return 0;
}
