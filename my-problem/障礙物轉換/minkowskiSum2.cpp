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
vector<Pt> monotone(vector<Pt> p) {
    vector<Pt> ch;
    ch.resize(p.size() * 2);
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
    return vector<Pt>(ch.begin(), ch.begin()+m-1);
}
//
const int MAXN = 512;
double calcArea(vector<Pt> p) {
    int n = (int) p.size();
    
    if (n < 3)   return 0.0;
    double ret = 0;
    for (int i = 0; i < n; i++)
        ret += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1)%n].x;
    return fabs(ret)/2;
}
void minkowskiSum(vector<Pt> A, vector<Pt> B) {
    vector<Pt> cA, cB, cC, C;
    int n, m;
    
    cA = monotone(A), cB = monotone(B);
    n = (int) cA.size(), m = (int) cB.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C.push_back(cA[i] + cB[j]);
        }
    }
    cC = monotone(C);
//    for (int i = 0; i < cC.size(); i++) {
//        printf("%lf %lf\n", cC[i].x, cC[i].y);
//    }
    printf("%.1lf\n", calcArea(cC));
}
int main() {
    int testcase, cases = 0;
    int N, M;
    Pt Np[MAXN], Mp[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%lf %lf", &Np[i].x, &Np[i].y);
            Np[i] = Pt(-Np[i].x, -Np[i].y);
        }
        scanf("%d", &M);
        for (int i = 0; i < M; i++)
            scanf("%lf %lf", &Mp[i].x, &Mp[i].y);
        
        printf("Case #%d: ", ++cases);
        minkowskiSum(vector<Pt>(Np, Np+N), vector<Pt>(Mp, Mp+M));
    }
    return 0;
}
/*
2 

5
-1 -1
-1 1
0 3
1 1
1 -1

4
1 1
8 2
12 -1
6 -4

3
-1 -4
-1 1
1 1

5 
1 0
6 5
10 5
10 -3
1 -3 
 */


