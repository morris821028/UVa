#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
#define MAXN 1024
#define MAXM 1024
int dp[MAXM][10][10]; // [previous i-th complete][diff i+1][diff i+2]
int main() {
    char s1[MAXM], s2[MAXM];
    while (scanf("%s %s", s1, s2) == 2) {
        int n = (int) strlen(s1);
        memset(dp, 63, sizeof(dp));
        dp[0][0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    int r = (s2[i] - s1[i] + 20 - j)%10;    // rotate up
                    for (int p = 0; p <= r; p++) {          // rotate i+1-th
                        for (int q  = 0; q <= p; q++) {     // rotate i+2-th
                            dp[i+1][(k+p)%10][q] = min(dp[i+1][(k+p)%10][q],
                                                               dp[i][j][k] + r);
                        }
                    }
                    r = (10 - r)%10;    // rotate down
                    for (int p = 0; p <= r; p++) {          // rotate i+1-th
                        for (int q  = 0; q <= p; q++) {     // rotate i+2-th
                            dp[i+1][(k-p+10)%10][(10-q)%10] = min(dp[i+1][(k-p+10)%10][(10-q)%10],
                                dp[i][j][k] + r);
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[n][0][0]);
    }
    return 0;
}
/*
*/