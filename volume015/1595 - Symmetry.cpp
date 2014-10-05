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
    int testcase, n;
    int x[1024], y[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
        }
        int mx, mn;
        mx = mn = x[0];
        for (int i = 0; i < n; i++) {
            mx = max(mx, x[i]);
            mn = min(mn, x[i]);
        }
        double mid = (mx + mn)/ 2.0;
        set< pair<int, int> > S;
        for (int i = 0; i < n; i++)
            S.insert(make_pair((int)((x[i] - mid) * 2), y[i]));
        int ret = 1;
        for (int i = 0; i < n && ret; i++) {
            ret &= S.find(make_pair((int)(-(x[i] - mid) * 2), y[i])) != S.end();
        }
        puts(ret ? "YES" : "NO");
    }
    return 0;
}
/*
 3
 5
 -2 5
 0 0
 6 5
 4 0
 2 3
 4
 2 3
 0 4
 4 0
 0 0
 4
 5 14
 6 10
 5 10 
 6 14
*/