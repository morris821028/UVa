#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <string.h>
#include <vector>
using namespace std;
#define MAXN 50
const double pi = acos(-1);
int N, M;
double P[MAXN], g[MAXN][MAXN], tri[MAXN][MAXN][MAXN], dp[MAXN][MAXN][MAXN];
double dist(double p) {
    if (p > 0.5)
        p = 1 - p;
    return 2 * sin(p * pi);
}
double getArea(double a, double b, double c) {
    double s = (a + b + c)/2;
    return sqrt(s * (s-a) * (s-b) * (s-c));
}
int main() {
    while (scanf("%d %d", &N, &M) == 2 && N) {
        for (int i = 0; i < N; i++)
            scanf("%lf", &P[i]);
        
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                g[i][j] = g[j][i] = dist(P[j] - P[i]);
            }
        }
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (i == j || j == k || k == i)
                        continue;
                    double t = getArea(g[i][j], g[j][k], g[k][i]);
                    tri[i][j][k] = t;
                }
            }
        }
        
        memset(dp, 0, sizeof(dp));
        for (int i = 3; i <= M; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = j+1; k < N; k++) {
                    for (int p = k+1; p < N; p++) {
                        dp[j][p][i] = max(dp[j][p][i], dp[j][k][i-1] + tri[j][k][p]);
                    }
                }
            }
        }
        
        double ret = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i+1; j < N; j++) {
                ret = max(ret, dp[i][j][M]);
            }
        }
        printf("%.6lf\n", ret);
    }
    return 0;
}
/*
 
*/