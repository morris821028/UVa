#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int set;
} ele;
ele D[1000005];
int cmp(const void *i, const void *j) {
    static ele *a, *b;
    static int va, vb, xa, xb, ya, yb;
    a = (ele *)i, b = (ele *)j;
    va = (a->set>>20)&1023;
    vb = (b->set>>20)&1023;
    if(va != vb)
        return va - vb;
    xa = (a->set>>10)&1023;
    xb = (b->set>>10)&1023;
    if(xa != xb)
        return xb - xa;
    ya = a->set&1023;
    yb = b->set&1023;
    return yb - ya;
}
int BIT[1001][1001], lowbit[1001];
int t, R, C, i, j, v;
int query(int x, int y) {
    int sum = 0, i, j;
    for(i = x; i > 0; i -= lowbit[i]) {
        for(j = y; j > 0; j -= lowbit[j]) {
            sum += BIT[i][j];
            if(sum >= 1000000007)
                sum -= 1000000007;
        }
    }
    return sum;
}
void modify(int x, int y, int v) {
    int i, j;
    for(i = x; i <= R; i += lowbit[i]) {
        for(j = y; j <= C; j += lowbit[j]) {
            BIT[i][j] += v;
            if(BIT[i][j] >= 1000000007)
                BIT[i][j] -= 1000000007;
        }
    }
}
int main() {
    for(i = 0; i <= 1000; i++)
        lowbit[i] = i&(-i);
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &R, &C);
        int m = 0, x, y;
        for(i = 0; i < R; i++) {
            for(j = 0; j < C; j++) {
                scanf("%d", &v);
                D[m].set = (v<<20)|(i<<10)|j;
                m++;
            }
        }
        qsort(D, m, sizeof(ele), cmp);
        for(i = 0; i <= R; i++)
            for(j = 0; j <= C; j++)
                BIT[i][j] = 0;
        for(i = 0; i < m; i++) {
            x = (D[i].set>>10)&1023, y = D[i].set&1023;
            int tmp = query(x+1, y+1);
            tmp++;
            modify(x+1, y+1, tmp);
        }
        printf("%d\n", query(R, C));
    }
    return 0;
}
