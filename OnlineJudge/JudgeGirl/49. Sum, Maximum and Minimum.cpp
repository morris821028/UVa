#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MIN(x,y) (x) < (y) ? (x) : (y)
#define MAX(x,y) (x) > (y) ? (x) : (y)
int main() {
    int n, m, x, p;
    int ret[1005][3];
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 0; i < m; i++)
            ret[i][0] = 0, ret[i][1] = INT_MIN, ret[i][2] = INT_MAX;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            p = abs(x)%m;
            ret[p][0] += x;
            ret[p][1] = MAX(ret[p][1], x);
            ret[p][2] = MIN(ret[p][2], x);
        }
        for (int i = 0; i < m; i++)
            printf("%d %d %d\n", ret[i][0], ret[i][1], ret[i][2]);
    }
    return 0;
}