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

double dp[1048576], sum[1048576];
int main() {
    int testcase, cases = 0;
    int n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            if (i <= m) {
                dp[i] = 1;
            } else {
                dp[i] = 1 + sum[i - m - 1] * 2.0 / i;
            }
            sum[i] = sum[i - 1] + dp[i];
        }
        printf("Case #%d: %.4lf\n", ++cases, dp[n]);
    }
    return 0;
}

/*
 3
 4 2
 7 2
 10 3
 */