#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
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
    double angle;
    int label;
    Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
        // angle = atan2(e.y - s.y, e.x - s.x);
    }
    bool operator<(const Seg &other) const {
        if (fabs(angle - other.angle) > eps)
            return angle > other.angle;
        if (cross(other.s, other.e, s) > -eps)
            return true;
        return false;
    }
    bool operator!=(const Seg &other) const {
        return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
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
Pt rotateRadian(Pt a, double sin, double cos) {
    double x, y;
    x = a.x * cos - a.y * sin;
    y = a.x * sin + a.y * cos;
    return Pt(x, y);
}
const double pi = acos(-1);
#define MAXN 1024
#define ITLIMIT 100
#define INF 1e+30
Pt D[MAXN];
double mileSum[MAXN];
int N, M;
vector< pair<int, double> > g[MAXN];
void getMinCostToSeg(int u, int sx, int sy, int F) {
    Pt p = D[u], as = D[sx], ae = D[sy];
    if (fabs(cross(p, as, ae)) < eps) {
        return ;
    }
    Pt vse = as - ae;
    swap(vse.x, vse.y), vse.x = -vse.x;
    Pt q = getIntersect(Seg(as, ae), Seg(p, p + vse));
    double sin = 1.0 / F;
    double cos = sqrt(1 - sin * sin);
//    printf("------- %lf %lf %lf %lf\n", q.x, q.y, p.x, p.y);
    Pt end;
    end = getIntersect(Seg(as, ae), Seg(p, p + rotateRadian(q - p, sin, cos)));
    
    if (between(as, ae, end)) { // new point `end`
//        printf("%lf %lf\n", end.x, end.y);
        int v = ++M;
        double w = (p - end).length() * F;
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
        mileSum[v] = mileSum[sx] + (end - as).length();
    }
    end = getIntersect(Seg(as, ae), Seg(p, p + rotateRadian(q - p, -sin, cos)));
    
    if (between(as, ae, end)) {
//        printf("%lf %lf\n", end.x, end.y);
        int v = ++M;
        double w = (p - end).length() * F;
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
        mileSum[v] = mileSum[sx] + (end - as).length();
    }
}
double spfa(int st, int ed) {
    double dist[MAXN];
    int inq[MAXN] = {}, u, v;
    queue<int> Q;
    for (int i = 0; i <= M; i++)
        dist[i] = INF;
    dist[st] = 0, Q.push(st);
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        inq[u] = 0;
        if (dist[u] > dist[ed]) {
            continue;
        }
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first;
            if (dist[v] > dist[u] + g[u][i].second) {
                dist[v] = dist[u] + g[u][i].second;
                if (!inq[v]) {
                    inq[v] = 1;
                    Q.push(v);
                }
            }
        }
    }
    return dist[ed];
}
int main() {
    int F, cases = 0;
    while (scanf("%d %d", &N, &F) == 2 && N) {
        for (int i = 0; i <= N; i++)
            D[i].read();
        for (int i = 0; i < MAXN; i++)
            g[i].clear();
        mileSum[0] = 0;
        for (int i = 1; i <= N; i++)
            mileSum[i] = mileSum[i-1] + (D[i] - D[i-1]).length();
        M = N;
        for (int i = 0; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == j || i+1 == j)
                    continue;
                getMinCostToSeg(i, j-1, j, F);
            }
            for (int j = 0; j <= N; j++) {
                g[i].push_back(make_pair(j, (D[i] - D[j]).length() * F));
            }
        }
        vector< pair<double, int> > A;
        for (int i = 0; i <= M; i++)
            A.push_back(make_pair(mileSum[i], i));
        sort(A.begin(), A.end());
        for (int i = 0; i+1 <= M; i++) {
            int u = A[i].second, v = A[i+1].second;
            g[u].push_back(make_pair(v, mileSum[v] - mileSum[u]));
        }
        printf("Case %d: %.10lf\n", ++cases, spfa(0, N));
    }
    return 0;
}
/*
 2 5
 0 0
 5 0
 10 0
 
 2 2
 0 0
 2 2
 2 -2
 
 3 5
 0 0
 1 1
 -7 0
 1 10
 
 2 2
 0 0
 2 2.1
 2 -2
 
 3 5
 0 1
 1 6
 5 1
 4 4
 
 0 0
 */