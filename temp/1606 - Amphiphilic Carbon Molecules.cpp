#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-8
#define MAXN 131072
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
Pt D[1024];
bool cmp(pair<double, Pt> a, pair<double, Pt> b) {
    return a.first < b.first;
}
int main() {
    int N, x, y, c;
    while (scanf("%d", &N) == 1 && N) {
        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &x, &y, &c);
            D[i] = Pt(x, y, c);
        }
        
        int ret = 0;
        for (int i = 0; i < N; i++) {
            vector< pair<double, Pt> > A;
            for (int j = 0; j < N; j++) {
                if (i == j)
                    continue;
                Pt p = D[j] - D[i];
                if (D[j].label)
                    p.x = -p.x, p.y = -p.y; // rotate 180 deg.
                A.push_back(make_pair(atan2(p.y, p.x), p));
            }
            sort(A.begin(), A.end(), cmp);
            int M = (int)A.size();
            int l = 0, r = 0, cnt = 1;
            for (l = 0; l < M; l++) {
                if (l == r)
                    r = (r+1)%M, cnt++;
                while (l != r && cross2(A[l].second, A[r].second) >= 0) {
                    r = (r+1)%M, cnt++;
                }
                ret = max(ret, cnt);
                cnt--;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}