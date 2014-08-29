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

struct Interval {
    int l, r;
    bool operator<(const Interval &a) const {
        return l < a.l || (l == a.l && r < a.r);
    }
};
int main() {
    int n, m;
    const int mod = 100000000;
    Interval D[128];
    while(scanf("%d %d", &m, &n) == 2 && n+m) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &D[i].l, &D[i].r);
        }
        sort(D, D+n);
        int dp[128][128] = {}; // [prev][now]
        int ret = 0;
        for (int i = 0; i < n; i++) {
            dp[i][i] = (D[i].l == 0);
            for (int j = i+1; j < n; j++) {
                if (D[j].l > D[i].l && D[j].r > D[i].r && D[j].l <= D[i].r) {
                    for (int k = 0; k <= i; k++) {
                        if (D[k].r >= D[j].l && k != i)
                            continue;
                        dp[i][j] = (dp[i][j] + dp[k][i])%mod;
                    }
                }
            }
            if (D[i].r == m) {
                for (int j = 0; j <= i; j++)
                    ret = (ret + dp[j][i])%mod;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 9 9
 2 7
 3 5
 6 8
 5 6
 2 8
 2 6
 0 2
 7 9
 2 8
 
 18 9
 8 15
 1 17
 0 10
 9 18
 12 15
 1 5
 5 6
 0 10
 11 17
 
 8 7
 0 3
 2 5
 5 8
 1 3
 3 6
 4 6
 0 2
 1 1
 0 1
 2 1
 0 1
 0 0
 */