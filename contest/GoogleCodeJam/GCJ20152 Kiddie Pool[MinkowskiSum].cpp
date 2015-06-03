#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-6

struct Pt {
    double x, y;
    int label;
    Pt(double a = 0, double b = 0, int c = 0):
    x(a), y(b), label(c) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
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
bool cmp(const Pt& p1, const Pt& p2)
{
    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
    if (p1.y * p2.y < 0) return p1.y > p2.y;
    double c = cross2(p1, p2);
    return c > 0 || (c == 0 && fabs(p1.x) < fabs(p2.x));
}
Pt getIntersect(Pt as, Pt ae, Pt bs, Pt be) {
    Pt u = as - bs;
    double t = cross2(be - bs, u)/cross2(ae - as, be - bs);
    return as + (ae - as) * t;
}
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
//
const int MAXN = 128;
int N;
double R[MAXN], C[MAXN], V, X;
void solveWithMinkowskiSum() {
    vector<Pt> P;
    for (int i = 0; i < N; i++)
        P.push_back(Pt(R[i], R[i]*C[i]));
    sort(P.begin(), P.end(), cmp);  // solar sort
    
    vector<Pt> convex;
    double mxFlow = 0;              // in unit time with temperature X
    Pt u, v, o(0, 0), to(1, X);     // y = (X) x, maximum x
    
    u = v = Pt(0, 0);
    convex.push_back(u);
    for (int i = 0; i < N; i++) {
        v = u + P[i];
        u = v;
        convex.push_back(v);
    }
    
    reverse(convex.begin(), convex.end());
    u = v = Pt(0, 0);
    for (int i = N-1; i >= 0; i--) {
        v = u + P[i];
        u = v;
        convex.push_back(v);
    }
    
    for (int i = 0, j = (int) convex.size()-1; i < convex.size(); j = i++) {
        u = convex[j], v = convex[i];
        if (cmpZero(cross(o, to, u)) * cmpZero(cross(o, to, v)) < 0) {
            Pt in = getIntersect(o, to, u, v);
            mxFlow = max(mxFlow, in.x);
        }
        if (cmpZero(cross(o, to, v)) == 0)
            mxFlow = max(mxFlow, v.x);
    }
    
    if (fabs(V) < eps)
        printf("%.10lf\n", 0.0);
    else if (fabs(mxFlow) < eps)
        puts("IMPOSSIBLE");
    else
        printf("%.10lf\n", V / mxFlow);
}
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %lf %lf", &N, &V, &X);
        
        V *= 10000, X *= 10000;
        for (int i = 0; i < N; i++) {
            scanf("%lf %lf", &R[i], &C[i]);
            R[i] *= 10000, C[i] *= 10000;
        }
        
        printf("Case #%d: ", ++cases);
        solveWithMinkowskiSum();
    }
    return 0;
}
/*
 6
 1 10.0000 50.0000
 0.2000 50.0000
 2 30.0000 65.4321
 0.0001 50.0000
 100.0000 99.9000
 
 1
 2 0.0001 0.1001
 0.0001 0.1003
 0.0001 0.1000

 */


