#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Point {
    double x, y, w;
};
double _random() {
    return (double) rand() / RAND_MAX;
}
double h_func(double x, double y, Point p[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += p[i].w * ((p[i].x-x)*(p[i].x-x)+(p[i].y-y)*(p[i].y-y));
    return sum;
}
double annealing(Point p[], int n) {
    const double S_MUL = 0.5f;
    const double S_LEN = 1000;
    const int T_CNT = 10;
    const int E_CNT = 100;
    double step = S_LEN;
    double x[E_CNT], y[E_CNT], val[E_CNT];
    double Lx, Ly, Rx, Ry, tx, ty, tcost;
    Lx = Rx = p[0].x;
    Ly = Ry = p[0].y;
    for (int i = 0; i < n; i++) {
        Lx = min(Lx, p[i].x), Rx = max(Rx, p[i].x);
        Ly = min(Ly, p[i].y), Ry = max(Ry, p[i].y);
    }
    for (int i = 0; i < E_CNT; i++) {
        x[i] = _random() * (Rx - Lx) + Lx;
        y[i] = _random() * (Ry - Ly) + Ly;
        val[i] = h_func(x[i], y[i], p, n);
    }
    while (step > 0.01) {
        for (int i = 0; i < E_CNT; i++) {
            for (int j = 0; j < T_CNT; j++) {
                tx = x[i] + _random() * 2 * step - step;
                ty = y[i] + _random() * 2 * step - step;
                tcost = h_func(tx, ty, p, n);
                if (tcost < val[i])
                    val[i] = tcost, x[i] = tx, y[i] = ty;
            }
        }
        step *= S_MUL;
    }
    double ret = val[0];
    for (int i = 0; i < n; i++)
        ret = min(ret, val[i]);
    return ret;
}
double solve(Point p[], int n) {
    double cx = 0, cy = 0, cw = 0;
    for (int i = 0; i < n; i++) {
        cx += p[i].x * p[i].w;
        cy += p[i].y * p[i].w;
        cw += p[i].w;
    }
    cx /= cw, cy /= cw;
    return h_func(cx, cy, p, n);
}
int main() {
    int n;
    Point p[128];
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].w);
        printf("%.3lf\n", solve(p, n));
    }
    return 0;
}