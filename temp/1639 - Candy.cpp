#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
// \sum i * C(2n-i, n) p^n+1 (1-p)^n-i +
//      i * C(2n-i, n) (1-p)^n+1 p^n-i
#define MAXN 526288
long double f[MAXN] = {};
long double logC(int n, int m) {
    return f[n] - f[m] - f[n-m];
}
int main() {
    for (int i = 1; i < MAXN; i++)
        f[i] = f[i-1] + log(i);
    int N, cases = 0;
    double p;
    while (scanf("%d %lf", &N, &p) == 2) {
        double ret = 0;
        long double p1 = log(p), p2 = log(1-p);
        for (int i = 1; i <= N; i++) {
            ret += i * exp(logC(2*N-i, N) + p1*(N+1) + p2*(N-i));
            ret += i * exp(logC(2*N-i, N) + p2*(N+1) + p1*(N-i));
        }
        printf("Case %d: %.6lf\n", ++cases, ret);
    }
    return 0;
}
/*
 10 0.400000
 100 0.500000
 124 0.432650
 325 0.325100
 532 0.487520
 2276 0.720000
*/