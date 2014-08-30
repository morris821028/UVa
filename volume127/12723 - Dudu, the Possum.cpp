#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int main() {
    int testcase, cases = 0;
    int n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        double p[128], e[512], C, X;
        for (int i = 1; i <= m; i++) {
            scanf("%lf", &p[i]);
        }
        
        for (int i = 1; i <= n; i++) {
            int q;
            scanf("%d", &q);
            e[i] = 0;
            for (int j = 0; j < q; j++) {
                scanf("%lf %lf", &C, &X);
                e[i] += C * X;
            }
        }
        
        double dp[512] = {}, ret = 0;
        dp[1] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; i+j <= n && j <= m; j++) {
                dp[i+j] += dp[i] * p[j];
            }
        }
        for (int i = 1; i <= n; i++) {
            ret += dp[i] * e[i];
        }
        printf("Case #%d: %.6lf\n", ++cases, ret);
    }
    return 0;
}

/*
 2
 2 1
 1.0
 2 50 0.5 100 0.5
 2 10 0.5 20 0.5
 5 2
 0.3 0.7
 5 10 0.2 20 0.3 5 0.1 25 0.35 2 0.05
 2 20 0.4 40 0.6
 1 4 1.0
 3 30 0.8 3 0.1 4 0.1
 10 1 0.1 2 0.1 3 0.1 4 0.1 5 0.1 6 0.1 7 0.1 8 0.1 9 0.1 10 0.1 
 */