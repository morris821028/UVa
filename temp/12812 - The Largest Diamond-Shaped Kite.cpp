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
#include <map>
using namespace std;
char g[512][512];
int dp[512][512];
int main() {
    int testcase;
    int n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%s", g[i]);
        }
        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == '#') {
                    int v1, v2, v3;
                    v1 = i-1 >= 0 && j-1 >= 0 ? dp[i-1][j-1] : 0;
                    v2 = i-2 >= 0 ? dp[i-2][j] : 0;
                    v3 = i-1 >= 0 && j+1 < m ? dp[i-1][j+1] : 0;
                    if (i-1 >= 0 && g[i-1][j] == '#')
                        dp[i][j] = min(v1, min(v2, v3)) + 1;
                    else
                        dp[i][j] = 1;
                } else {
                    dp[i][j] = 0;
                }
                ret = max(ret, dp[i][j]);
            }
        }
        printf("%d\n", ret * 2 - 1 < 0 ? 0 : ret * 2 - 1);
    }
    return 0;
}
/*
 2
 3 3
 .#.
 ###
 .#.
 8 10
 ..##...#..
 .###..###.
 ..#.......
 ....##....
 ....######
 ...#####..
 ..########
 .....#....
 */