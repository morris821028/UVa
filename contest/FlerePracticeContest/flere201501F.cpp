#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-8
struct Pt {
    long long x, y;
    Pt(long long a = 0, long long b = 0):
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
        return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Pt &a) const {
        if (x - a.x == 0)
            return x < a.x;
        if (y - a.y == 0)
            return y < a.y;
        return false;
    }
    long long length() {
        return x * x + y * y;
    }
    void read() {
        scanf("%lld %lld", &x, &y);
    }
};
long long dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
long long llabs(long long x) {
    return x < 0 ? -x : x;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        Pt A, B, C;
        A.read();
        B.read();
        C.read();
        long long area = llabs(cross(A, B, C));
        if (area == 0) {
            puts("0");
        } else {
            long long la, lb, lc;
            int pt = 0;
            la = (B - C).length();
            lb = (A - C).length();
            lc = (A - B).length();
            if (la == lb || lb == lc || lc == la)
                pt += 1;
            if (la == lb && lb == lc)
                pt += 2;
            if (la + lb == lc || lb + lc == la || la + lc == lb) {
                pt += 4;
            } else if (dot(B - A, C - A) > 0 && dot(A - B, C - B) > 0 && dot(A - C, B - C) > 0) {
                pt += 16;
            } else {
                pt += 8;
            }
            printf("%d\n", pt);
        }
    }
    return 0;
}
/*
 3
 0 0 0 3 4 0
 0 0 4 0 2 4
 0 0 10 0 5 1
*/