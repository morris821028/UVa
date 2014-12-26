#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f

int polar[360 * 2][128];

int solve(int H, int A, int R) {
    int ret = 0;
    for (int h = H; h <= R; h++) {
        int sum = 0;
        for (int i = 0; i < 720; i++) {
            sum += polar[i][h] - polar[i][h - H];
            if (i - A - 1 >= 0)
                sum -= polar[i - A - 1][h] - polar[i - A - 1][h - H];
            ret = max(ret, sum);
        }
    }
    return ret;
}
int main() {
    int N, R, E, H, A;
    int r, theta;
    while (scanf("%d %d", &N, &R) == 2 && N) {
        
        memset(polar, 0, sizeof(polar));
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &r, &theta);
            polar[theta][r]++;
            polar[theta + 360][r]++;
        }
        
        for (int i = 0; i < 360 * 2; i++) {
            for (int j = 1; j <= R; j++) {
                polar[i][j] += polar[i][j-1];
            }
        }
        
        scanf("%d", &E);
        for (int i = 0; i < E; i++) {
            scanf("%d %d", &H, &A);
            int ret = solve(H, A, R);
            printf("%d\n", ret);
        }
    }
    return 0;
}
/*
 6 100
 15 7
 15 60
 40 15
 50 15
 45 30
 45 90
 2
 2 1
 100 359
 
 9 100
 15 7
 15 60
 40 15
 50 15
 45 30
 45 90
 40 45
 50 45
 78 100
 6
 100 359
 11 30
 10 30
 11 29
 5 30
 11 10
 0 0
 */
