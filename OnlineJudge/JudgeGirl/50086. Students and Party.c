#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static int e[1<<23][2], mark[(1<<16)>>5];
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
#define WAT(x) (ret[x>>5]>>(x&31)&1)
#define RET(x) (ret[x>>5] |= 1<<(x&31))
int main() {
    int n, m, x;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &e[i][0], &e[i][1]);
    while (scanf("%d", &x) == 1)
        SET(x);
    static int ret[(1<<16)>>5];
    for (int i = 0; i < m; i++) {
        int u = e[i][0], v = e[i][1];
        if (GET(u) || GET(v))
            RET(u), RET(v);
    }
    for (int i = 0; i < n; i++) {
        if (!WAT(i) && !GET(i))
            printf("%d\n", i);
    }
    return 0;
}

