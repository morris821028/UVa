#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <stdlib.h>
#include <vector>
#include <time.h>
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
vector<Pt> monotone(vector<Pt> p) {
    Pt ch[1024];
    sort(p.begin(), p.end());
    int m = 0, n = (int) p.size();
    for(int i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(int i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return vector<Pt>(ch, ch+m-1);
}
//
vector<Pt> generateSymConvex(int N) {
    vector<Pt> P;
    for (int i = 0; i < N; i++)
        P.push_back(Pt(rand()%128 + 1, rand()%512));
    sort(P.begin(), P.end(), cmp);  // solar sort
    
    vector<Pt> convex;
    Pt u, v, o(0, 0);     // y = (X) x, maximum x
    
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
    convex = monotone(convex);
    return convex;
}
// 
vector<Pt> generateConvex(int N) {
    vector<Pt> P;
    for (int i = 0; i < N; i++)
        P.push_back(Pt(rand()%128 - 64, rand()%512 - 50));
    P.push_back(Pt(0, 0));
    P = monotone(P);
    return P;
} 
int main() {
    srand (time(NULL));
    int testcase, n, m, x, y;
    
    testcase = 100;
    printf("%d\n\n", testcase);
    while (testcase--) {
        vector<Pt> va = generateConvex(512);
        vector<Pt> vb = generateConvex(512);
        n = (int) va.size();
        m = (int) vb.size();
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%.0lf %.0lf\n", va[i].x, va[i].y);
        }
        printf("%d\n", m);
        for (int i = 0; i < m; i++) {
            printf("%.0lf %.0lf\n", vb[i].x, vb[i].y);
        }
        puts("");
    }
    return 0;
}

