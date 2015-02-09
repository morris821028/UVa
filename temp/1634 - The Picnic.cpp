#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <string.h>
#include <vector>
using namespace std;
#define eps 1e-8
#define MAXN 128
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
        return x * x + y * y;
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
double dp[2][MAXN][MAXN];
int from[MAXN][MAXN], g[MAXN][MAXN];
const double pi = acos(-1);
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
int inTriangle(Pt a, Pt b, Pt c, Pt p) {
    if (cmpZero(cross(a, p, b)) * cmpZero(cross(a, p, c)) < 0) {
        if (cmpZero(cross(b, p, c)) * cmpZero(cross(b, p, a)) < 0) {
            return 1;
        }
    }
    return 0;
}
double subDp(vector<Pt> A) {
    sort(A.begin(), A.end());
    int N = (int) A.size(), mid[MAXN] = {};
    // [up/down][node][prev]
    for (int i = 0; i < N; i++) {
        int ok = 1;
        for (int j = 0; j < N; j++) {
            dp[0][i][j] = dp[1][i][j] = -1;
            if (i != j && onSeg(Pt(0, 0), A[i], A[j]))
                ok = 0;
        }
        mid[i] = ok;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            int ok = 1;
            for (int k = 0; k < N; k++) {
                if (inTriangle(Pt(0, 0), A[i], A[j], A[k])) {
                    ok = 0;
                    break;
                }
            }
            g[i][j] = ok;
        }
        dp[0][i][i] = 0;
        dp[1][i][i] = 0;
    }
//    for (int i = 0; i < N; i++) {
//        printf("%6.2lf %6.2lf\n", A[i].x, A[i].y);
//    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
//            if (dp[0][i][j] >= 0)
//            printf("0 [%d %d] %lf\n", i, j, dp[0][i][j]/2);
//            if (dp[1][i][j] >= 0)
//            printf("1 [%d %d] %lf\n", i, j, dp[1][i][j]/2);
            if (dp[0][i][j] < 0 && dp[1][i][j] < 0)
                continue;
            for (int k = i+1; k < N; k++) {
                if (g[i][k] && cmpZero(cross(A[j], A[i], A[k])) <= 0 &&
                    cmpZero(cross2(A[i], A[k])) <= 0 && dp[0][i][j] >= 0) {
                    if (i == j || mid[i]) {
                        double t = fabs(cross2(A[i], A[k]));
                        dp[0][k][i] = max(dp[0][k][i], dp[0][i][j] + t);
                    }
                }
                if (g[i][k] && cmpZero(cross(A[j], A[i], A[k])) >= 0 &&
                    cmpZero(cross2(A[i], A[k])) >= 0 && dp[1][i][j] >= 0) {
                    if (i == j || mid[i]) {
                        double t = fabs(cross2(A[i], A[k]));
                        dp[1][k][i] = max(dp[1][k][i], dp[1][i][j] + t);
                    }
                }
            }
        }
    }
    
    double ret = 0, up = 0, down = 0;
    for (int i = 0; i < N; i++) {
        up = 0, down = 0;
        for (int j = 0; j < N; j++) {
            up = max(up, dp[0][i][j]);
            down = max(down, dp[1][i][j]);
        }
        ret = max(ret, up);
        ret = max(ret, down);
//        printf("up %7.1lf down %7.1lf\n", up/2, down/2);
        if (!mid[i]) continue;
        ret = max(ret, up + down);
    }
//    printf("----------------- %lf\n", ret/2);
    return ret;
}
int main() {
    int testcase, N;
    Pt D[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            D[i].read();
        
        double ret = 0;
        for (int i = 0; i < N; i++) {
            vector<Pt> A;
            for (int k = 0; k < N; k++) {
                if (i == k) continue;
                if ((D[k] - D[i]).x >= 0)
                    A.push_back(D[k] - D[i]);
            }
            ret = max(ret, subDp(A));
        }
        printf("%.1lf\n", ret/2);
    }
    return 0;
}