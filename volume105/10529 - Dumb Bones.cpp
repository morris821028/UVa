#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

const double pi = acos(-1);
int main() {
    double pl, pr;
    int n;
    while (scanf("%d %lf %lf", &n, &pl, &pr) == 3 && n) {
        double dp[1024] = {};
        double p = 1 - pl - pr;
        dp[0] = 0, dp[1] = 1 / p;
        for (int i = 2; i <= n; i++) {
            dp[i] = 1e+30;
            for (int j = 0; j <= i; j++) {
                int l = j, r = i - j - 1;
                dp[i] = min(dp[i], dp[l] + dp[r] + (1 + dp[l] * pl + dp[r] * pr)/p);
            }
        }
        printf("%.2lf\n", dp[n]);
    }
    return 0;
}
/*
 10 3
 10 5
 10 7
 */