#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <assert.h>
#include <queue>
#include <algorithm>
using namespace std;
#define eps 1e-6
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
    double length2() {
        return x*x + y*y;
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
double distSeg2Point(Pt a, Pt b, Pt p) {
    Pt c, vab;
    vab = a - b;
    if (between(a, b, p)) {
        c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
        return (p - c).length();
    }
    return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
int cmpZero(double x) {
    if (fabs(x) < eps)  return 0;
    return x < 0 ? -1 : 1;
}
Pt projectLine(Pt as, Pt ae, Pt p) {
    double a, b, c, v;
    a = as.y - ae.y, b = ae.x - as.x;
    c = - (a * as.x + b * as.y);
    v = a * p.x + b * p.y + c;
    return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}
const double pi = acos(-1);

// this problem
void tangent_line(Pt p, Pt o, double r, Pt &b1, Pt &b2) { // p not in circle
    if (cmpZero((p - o).length() - r) == 0) {
        Pt vpo = p - o;
        b1 = p + Pt(-vpo.y, vpo.x);
        b2 = p + Pt(vpo.y, -vpo.x);
        return ;
    }
    double a, b, c, d; // (a, b), (c, d)
    double ma, mb, mc, sq;
    a = p.x, b = p.y, c = o.x, d = o.y;
    ma = (c-a)*(c-a) - r*r, mb = 2*(c-a)*(b-d), mc = (b-d)*(b-d) - r*r;
    sq = sqrt(mb*mb - 4*ma*mc);
//    printf("sq %lf %lf\n", sq, mb*mb - 4*ma*mc);
    if (cmpZero(ma) == 0) {
        b1 = p + Pt(1, -mc / mb);
        b2 = p + Pt(0, 1);
    } else if (cmpZero(sq) > 0) {
        b1 = p + Pt(1, (-mb + sq)/ 2 / ma);
        b2 = p + Pt(1, (-mb - sq)/ 2 / ma);
    } else {
        assert(false);
    }
}
const int MAXN = 32767;
Pt D[MAXN];

int main() {
    double H, W, R, Cx, Cy;
    int N, cases = 0;
    while (scanf("%lf %lf %lf %lf %lf %d", &H, &W, &R, &Cx, &Cy, &N) == 6 && H) {
        for (int i = 0; i < N; i++)
            D[i].read();
        
        Pt C(Cx, Cy);
        vector< pair<double, double> > interval;
        vector<Pt> boundary;
        vector<Pt> rect;
        double dist[4] = {0, W, W+H, W+H+W};
        double pm = W+W+H+H; // perimeter
        
        rect.push_back(Pt(0, 0));
        rect.push_back(Pt(W, 0));
        rect.push_back(Pt(W, H));
        rect.push_back(Pt(0, H));
        
        for (int i = 0; i < N; i++) {
            Pt b1, b2, c1, c2;
            tangent_line(D[i], C, R, b1, b2);
            c1 = projectLine(D[i], b1, C);
            c2 = projectLine(D[i], b2, C);
            
            if (cmpZero(cross(D[i], C, c1)) < 0)
                swap(c1, c2), swap(b1, b2);
            
//            printf("%lf %lf, %lf %lf\n", c1.x, c1.y, c2.x, c2.y);
            Seg line[2];
            line[0] = Seg(D[i], b1);
            line[1] = Seg(D[i], b2);
            
            double v[2] = {-1, -1};
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < rect.size(); k++) {
                    Seg s = Seg(rect[k], rect[(k+1)%rect.size()]);
                    if (cmpZero(cross(line[j].s, line[j].e, s.s)) *
                        cmpZero(cross(line[j].s, line[j].e, s.e)) <= 0) {
                        Pt p = getIntersect(s, line[j]);
                        if (cmpZero(dot(C - D[i], p - D[i])) >= 0) {
//                            printf("%lf %lf\n", p.x, p.y);
                            if ((j == 0 && cmpZero(cross(D[i], C, p)) >= 0) ||
                                (j == 1 && cmpZero(cross(D[i], C, p)) <= 0)) {
                                v[j] = dist[k] + (p - rect[k]).length();
                                break;
                            }
                        }
                    }
                }
            }
            
            assert(v[0] > -1 && v[1] > -1);
            if (v[0] > v[1]) {
//                printf("%d: [%lf %lf]\n", i, v[0], v[0] + pm - (v[0] - v[1]));
                interval.push_back(make_pair(v[0], v[0] + pm - (v[0] - v[1])));
                interval.push_back(make_pair(v[0] + pm, v[0] + pm - (v[0] - v[1]) + pm));
            } else {
//                printf("%d: [%lf %lf]\n", i, v[0], v[1]);
//                printf("%d: [%lf %lf]\n", i, v[0] + pm, v[1] + pm);
                interval.push_back(make_pair(v[0], v[1]));
                interval.push_back(make_pair(v[0] + pm, v[1] + pm));
            }
//            printf("%lf %lf\n", v[0], v[1]);
        }
        
        int ret = 0;
        priority_queue<double, vector<double>, greater<double> > pQ;
        sort(interval.begin(), interval.end());
        
        for (int i = 0; i < interval.size(); i++) {
            while (!pQ.empty() && cmpZero(pQ.top() - interval[i].first) < 0)
                pQ.pop();
            pQ.push(interval[i].second);
            ret = max(ret, (int) pQ.size());
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}

/*
 5 6 1 3 1 1
 3 3
 
 5 6 1 1 1 1
 3 3
 
 5 6 1 1 2 1
 3 3
 
 5 6 1 1 2 1
 4 3
 
 5 6 1 2 1 1
 3 4
 
 
 5 6 1 4 3 2
 3 3
 5 3
 
 5 6 1 4 3 1
 3 3
 
 5 6 1 4 3 5
 5 4
 5 2
 3 4
 3 2
 1 1
 
 5 6 1 4 3 4
 5 4
 5 2
 3 4
 3 2
 
 5 6 1 4 3 1
 2 1

 5 6 1 4 3 2
 2 1
 5 4
 
 5 6 1 4 3 3
 2 1
 5 4
 5 2
 
 5 6 1 4 3 4
 2 1
 5 4
 5 2
 2 4
 
 75 91 20 60 47 6
 39 10
 48 18
 72 21
 82 33
 18 36
 31 52
 
 0 0 0 0 0 0
*/