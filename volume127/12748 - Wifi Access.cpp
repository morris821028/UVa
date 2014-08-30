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

int main() {
    int testcase, n, m, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        int x[128], y[128], r[128];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &x[i], &y[i], &r[i]);
        }
        
        printf("Case %d:\n", ++cases);
        for (int i = 0; i < m; i++) {
            int px, py, dist, ok = 0;
            scanf("%d %d", &px, &py);
            for (int j = 0; j < n && !ok; j++) {
                dist = (x[j] - px)*(x[j] - px) + (y[j] - py)*(y[j] - py);
                if (dist <= r[j]*r[j])
                    ok = 1;
            }
            puts(ok ? "Yes" : "No");
        }
    }
    return 0;
}

/*
 1
 1 3
 0 0 2
 0 0
 0 2
 0 3
 */