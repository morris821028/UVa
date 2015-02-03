#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-8
#define MAXN 128
#define MAXM 1024
#define INF 0x3f3f3f3f
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
int N, M, C[MAXM], f[MAXM][MAXN], dp[MAXN][MAXN];
Pt D[MAXN], P[MAXM];
int main() {
    while (scanf("%d", &N) == 1 && N) {
        Pt center(0, 0);
        for (int i = 0; i < N; i++) {
            D[i].read();
            D[i+N] = D[i];
            center = center + D[i];
        }
        center.x /= N, center.y /= N;
        
        scanf("%d", &M);
        for (int i = 0; i < M; i++) {
            P[i].read();
            scanf("%d", &C[i]);
        }
        
        for (int i = 0; i < M; i++) {
            for (int j = 0, k = N-1; j < N; k = j++) {
                if (cross(D[k], D[j], center) * cross(D[k], D[j], P[i]) < 0) {
                    f[i][j] = f[i][j+N] = 1;
                } else {
                    f[i][j] = f[i][j+N] = 0;
                }
            }
        }
        
        memset(dp, 63, sizeof(dp));
        for (int i = 0; i < N; i++) {
            for (int j = 0; i + j < 2 * N; j++) {
                int l = j, r = j+i;
                dp[l][r] = INF;
                for (int k = 0; k < M; k++) {
                    for (int p = l; f[k][p] && p <= r; p++) {
                        dp[l][r] = min(dp[l][r], (p+1 <= r ? dp[p+1][r] : 0) + C[k]);
                    }
                    for (int p = r; f[k][p] && p >= l; p--) {
                        dp[l][r] = min(dp[l][r], (p-1 >= l ? dp[l][p-1] : 0) + C[k]);
                    }
                }
            }
        }
        int ret = INF;
        for (int i = 0; i < 2 * N; i++)
            ret = min(ret, dp[i][i+N-1]);
        if (ret != INF)
            printf("%d\n", ret);
        else
            printf("Impossible.\n");
    }
    return 0;
}
/*
*/