#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
    int testcase;
    int n, x[2048], y[2048];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        
        double sumx = 0, sumy = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
            sumx += x[i], sumy += y[i];
        }
        sumx /= n, sumy /= n;
        vector< pair<double, int> > D;
        for (int i = 0; i < n; i++) {
            D.push_back(make_pair(atan2(y[i] - sumy, x[i] - sumx), i));
        }
        sort(D.begin(), D.end());
        
        for (int i = 0; i < n; i++)
            printf("%d%c", D[i].second, i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
/*
 2
 4 0 0 2 0 0 1 1 0
 5 0 0 10 0 10 5 5 -1 0 5
 */