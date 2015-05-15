#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-8
struct Frac {
    long long x, y;
    Frac(long long a = 0, long long b = 1) {
        x = a, y = b;
        normal();
    }
    void normal() {
        if (y < 0)  x = -x, y = -y;
        long long g = llgcd(x, y);
        x /= g, y /= g;
        if (y < 0)  x = -x, y = -y;
    }
    long long llgcd(long long x, long long y) const {
        long long t;
        while (x%y)
            t = x, x = y, y = t % y;
        return y;
    }
    Frac operator-(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x - vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator+(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x + vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator*(const Frac a) const {
        long long g1 = llgcd(x, a.y), g2 = llgcd(a.x, y);
        long long va = 0, vb = 0;
        va = (x / g1) * (a.x / g2);
        vb = (y / g2) * (a.y / g1);
        return Frac(va, vb);
    }
    Frac operator/(const Frac a) const {
        long long g1 = llgcd(y, a.y), g2 = llgcd(x, a.x);
        long long va = 0, vb = 0;
        va = (a.y / g1) * (x / g2);
        vb = (y / g1) * (a.x / g2);
        return Frac(va, vb);
    }
    bool operator==(const Frac &a) const {
        return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Frac &a) const {
        return x * a.y < a.x * y;
    }
    void print() {
        printf("%lld/%lld", x, y);
    }
};
struct Pt {
    Frac x, y;
    Pt(Frac a = Frac(), Frac b = Frac()):
    x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const Frac a) const {
        return Pt(x * a, y * a);
    }
    bool operator==(const Pt &a) const {
        return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Pt &a) const {
        if (x - a.x == 0)
            return x < a.x;
        if (y - a.y == 0)
            return y < a.y;
        return false;
    }
    Frac length() {
        return x * x + y * y;
    }
    void print() {
        printf("(");
        x.print();
        printf(",");
        y.print();
        printf(")\n");
    }
};
struct Seg {
    Pt s, e;
    Seg(Pt a = Pt(), Pt b = Pt()):
    s(a), e(b) {}
    bool operator!=(const Seg &other) const {
        return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
    }
};
Frac dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
Frac cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
Frac cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    Frac t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
long long llabs(long long x) {
    return x < 0 ? -x : x;
}
int main() {
    int testcase;
    int x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        Pt A, B, C, D, E, F, O;
        int a, b, c, d;
        scanf("%d %d", &x, &y);
        A = Pt(Frac(x, 1), Frac(y, 1));
        scanf("%d %d", &x, &y);
        B = Pt(Frac(x, 1), Frac(y, 1));
        scanf("%d %d", &x, &y);
        C = Pt(Frac(x, 1), Frac(y, 1));
        scanf("%d %d %d %d", &a, &b, &c, &d);
        E = A + (C - A) * Frac(a, a+b);
        F = A + (B - A) * Frac(c, c+d);
        O = getIntersect(Seg(B, E), Seg(C, F));
        D = getIntersect(Seg(A, O), Seg(B, C));
        D.print();
    }
    return 0;
}
/*
 2 
 0 5 0 0 5 0
 1 1
 1 2
 1 4 3 6 7 9
 2 4
 3 6
 
 999
 5855 1336 7833 7261 5723 7823 
 6418 8453 
 3662 6640
*/