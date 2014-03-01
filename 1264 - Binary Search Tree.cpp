#include <stdio.h>
typedef struct{
    int l, r, v, p;
    int total;
} Node;
Node bnode[21];
int bsize;
int main() {
    int t, n, i, j, x;
    scanf("%d", &t);
    long long pascal[21][21] = {};
    pascal[0][0] = 1;
    for(i = 1; i <= 20; i++) {
        pascal[i][0] = 1;
        for(j = 1; j <= i; j++)
            pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
    }
    while(t--) {
        scanf("%d", &n);
        scanf("%d", &bnode[0].v);
        bnode[0].l = bnode[0].r = 0;
        bnode[0].p = -1;
        bnode[0].total = 1;
        bsize = 0;
        for(i = 1; i < n; i++) {
            scanf("%d", &x);
            int idx = 0;
            while(true) {
                bnode[idx].total++;
                if(bnode[idx].v > x) {
                    if(bnode[idx].l) {
                        idx = bnode[idx].l;
                    } else {
                        bnode[idx].l = ++bsize;
                        break;
                    }
                } else {
                    if(bnode[idx].r) {
                        idx = bnode[idx].r;
                    } else {
                        bnode[idx].r = ++bsize;
                        break;
                    }
                }
            }
            bnode[bsize].v = x;
            bnode[bsize].l = bnode[bsize].r = 0;
            bnode[bsize].p = idx;
            bnode[bsize].total = 1;
        }
        long long ans = 1;
        int x, y;
        for(i = 0; i < n; i++) {
            if(bnode[i].p != -1) {
                if(bnode[bnode[i].p].r == i) {
                    if(bnode[bnode[i].p].l) {
                        x = bnode[i].total;
                        y = bnode[bnode[bnode[i].p].l].total;
                        ans *= pascal[x+y][y];
                        ans %= 9999991;
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
