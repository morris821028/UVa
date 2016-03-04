#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Leg {
    double mile, f20, f40;
} legs[1024];
const double VCRUISE = 400;
const double AOPT = 30000;
const double GPHOPT = 2000;
const double GPHEXTRA = 10;
const double CLIMBCOST = 50;
const int MAXN = 1024;	// maximum #legs
const int MAXH = 45;	// between 20,000 and 40,000 feet
const double DINF = 1e+20;
double inter(Leg a, double h) {
    return a.f20 + (a.f40 - a.f20) * (h - 20000) / (40000 - 20000);
}
void solve(int n) {
    double dp[MAXN][MAXH];
    int from[MAXN][MAXH];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= 40; j++)
            dp[i][j] = DINF;
    }
    
    dp[0][0] = 0;	// leg 0: altitude 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 40; j++) {
            if (dp[i][j] >= DINF)
                continue;
            double alti_a = j * 1000.f;
            for (int k = 20; k <= 40; k++) {
                double cc = 0, alti_b;
                alti_b = k * 1000.f;
                
                if (alti_b > alti_a)
                    cc += CLIMBCOST * (alti_b - alti_a) / 1000.f;
                double v = VCRUISE + inter(legs[i+1], alti_b);
                if (v <= 0)
                	continue;
                double c = fabs(alti_b - AOPT) * GPHEXTRA / 1000.f + GPHOPT;
                cc += c * legs[i+1].mile / v;
                if (dp[i][j] + cc < dp[i+1][k])
                    dp[i+1][k] = dp[i][j] + cc, from[i+1][k] = j;
            }
        }
    }
    
    double ret = DINF;
    int last = -1;
    vector<int> solution;
    for (int i = 20; i <= 40; i++) {
        if (dp[n][i] < ret)
            ret = dp[n][i], last = i;
    }
    for (int i = n; i > 0; i--) {
        solution.push_back(last);
        last = from[i][last];
    }
    for (int i = n-1; i >= 0; i--)
        printf(" %d", solution[i]);
    // tricky 
    printf(" %.0lf\n", ceil(ret));
}
int main() {
    int testcase, cases = 0;
    int n;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lf %lf %lf",
                  &legs[i].mile, &legs[i].f20, &legs[i].f40);
        }
        printf("Flight %d:", ++cases);
        solve(n);
    }
    return 0;
}

