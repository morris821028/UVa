#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
    double length() {
        return hypot(x, y);
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
};
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
struct Seg {
    Pt s, e;
    Seg(Pt a = Pt(), Pt b = Pt()): s(a), e(b) {
        // angle = atan2(e.y - s.y, e.x - s.x);
    }
};
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
    return acos(dot(va, vb) / va.length() / vb.length());
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
}
const double pi = acos(-1);
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
double getArea(double a, double b, double c) {
    double s = (a + b + c)/2;
    return sqrt(s * (s-a) * (s-b) * (s-c));
}
int main() {
    int N;
    Pt A, B, vAB;
    double L[16];
    while (scanf("%d", &N) == 1 && N) {
        A.read(), B.read();
        double sum = 0, sq2 = 0;
        vAB = Pt(0, 0);
        for (int i = 0; i < N; i++) {
            scanf("%lf", &L[i]);
            vAB = vAB + Pt(L[i], -L[i]);
            sum += L[i], sq2 += L[i] * L[i] /2;
        }
        sum *= sqrt(2);
        Pt nB = getIntersect(Seg(A, A+vAB), Seg(Pt(0, 0), B));
        double area = fabs(cross2(A, nB))/2;
        area *= pow(sum / (A - nB).length(), 2);
        printf("%.3lf\n", area - sq2);
    }
    return 0;
}